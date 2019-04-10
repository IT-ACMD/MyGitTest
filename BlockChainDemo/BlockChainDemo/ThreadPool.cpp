#include "stdafx.h"
#include <process.h>
#include "ThreadPool.h"

#include <algorithm>
#include <functional>
#include <process.h>

/* structure definition -------------------------------------------------------------------*/

struct Thread
{
	HANDLE  _hHandle;
	void    (*_pfTask)(void*,void*);
	void*   _pTaskArg;
	void*   _pTaskArg2;
	HCOND   _hTask;
	char    _bWorking;

	void*   _pNode[2];
};



struct Threadpool
{
	sizet     _nInitSize;
	sizet     _nMaxSize;
	sizet     _nTotalSize;
	sizet     _nMaxIdleSize;
	sizet     _nIdleSize;
	sizet     _nAvailLow;
	sizet     _nAvailHigh;
	sizet     _nBusySize;

	void*     _pBusyThreads[2];
	void*     _pIdleThreads[2];
	CSLOCK    _lockBusyThreads;
	CSLOCK    _lockIdleThreads;
	HCOND     _hIdleCond;
};



/**/
static Threadpool* _pThreadpool = 0;


void createThreads(sizet nSize);
void deleteThreads(sizet nSize);



unsigned __stdcall workThread(void* pArg)
{
	Thread* pThread = (Thread*)pArg;
    while(1)
    {
		while(!pThread->_pfTask && pThread->_bWorking)
			WAIT(pThread->_hTask);

		if(!pThread->_bWorking) return 0;
        if (pThread->_pfTask == 0) continue;

		pThread->_pfTask(pThread->_pTaskArg, pThread->_pTaskArg2);
		pThread->_pfTask = 0;

		LOCK(_pThreadpool->_lockBusyThreads);
		LQ_REMOVE(&pThread->_pNode);
		_pThreadpool->_nBusySize--;
		UNLOCK(_pThreadpool->_lockBusyThreads);

		LOCK(_pThreadpool->_lockIdleThreads);
		LQ_INSERT_TAIL(&_pThreadpool->_pIdleThreads, &pThread->_pNode);
		_pThreadpool->_nIdleSize++;
		UNLOCK(_pThreadpool->_lockIdleThreads);

		if(_pThreadpool->_nIdleSize > _pThreadpool->_nAvailHigh)
			deleteThreads(_pThreadpool->_nIdleSize - _pThreadpool->_nInitSize);
    }
	return 0;
}



/**/
void createThreads(sizet nSize)
{
	sizet i = 0;
	LOCK(_pThreadpool->_lockIdleThreads);
	while(i < nSize)
	{
		Thread* pThread = (Thread*)malloc(sizeof(Thread));
		//assert( pThread );
		pThread->_bWorking = true;
		pThread->_pfTask = 0;
		pThread->_pTaskArg = 0;
		pThread->_pTaskArg2 = 0;
		LQ_INSERT_TAIL(&_pThreadpool->_pIdleThreads, &pThread->_pNode);

		pThread->_hTask = CREATE_COND();
		pThread->_hHandle = (HANDLE)_beginthreadex(0, 0, workThread, pThread, 0, 0);

		_pThreadpool->_nIdleSize++;
		_pThreadpool->_nTotalSize++;
		i++;
	}
	UNLOCK(_pThreadpool->_lockIdleThreads);

	SIGNAL(_pThreadpool->_hIdleCond);
}



void deleteThreads(sizet nSize)
{
	sizet i = 0;
	LOCK(_pThreadpool->_lockIdleThreads);
	while(i < nSize)
	{
		S* pNode = LQ_HEAD(&_pThreadpool->_pIdleThreads);
		LQ_REMOVE(pNode);
		Thread* pThread = LQ_DATA(pNode, Thread, _pNode);
		pThread->_bWorking = 0;
		SIGNAL(pThread->_hTask);

		WaitForSingleObject(pThread->_hHandle, INFINITE);
		CloseHandle(pThread->_hHandle);
		
		free(pThread);
		_pThreadpool->_nIdleSize = 0;
	}
	UNLOCK(_pThreadpool->_lockIdleThreads);
}



/* interface function implementation ------------------------------------------------------*/

int initThreadpool(sizet nSize)
{
	if(_pThreadpool) return 1;

	sizet nInitSize = nSize == 0 ? 32 : nSize;

	Threadpool* pPool = (Threadpool*)malloc(sizeof(Threadpool));
	if(!pPool) return -1;

	pPool->_nInitSize = nInitSize;
	pPool->_nIdleSize = nInitSize;
	pPool->_nBusySize = 0;
	pPool->_nTotalSize = nInitSize;
	pPool->_nMaxSize = nInitSize + 20;
	pPool->_nAvailLow = (nInitSize - 10 > 0) ? (nInitSize - 10) : 3;
	pPool->_nAvailHigh = nInitSize + 10;

	LQ_INIT(&pPool->_pBusyThreads);
	LQ_INIT(&pPool->_pIdleThreads);
	CREATE_LOCK(pPool->_lockBusyThreads);
	CREATE_LOCK(pPool->_lockIdleThreads);
	pPool->_hIdleCond = CREATE_COND();

	sizet i = 0;
	while(i < nInitSize)
	{
		Thread* pThread = (Thread*)malloc(sizeof(Thread));
		//assert( pThread );
		pThread->_bWorking = true;
		pThread->_pfTask = 0;
		pThread->_pTaskArg = 0;
		pThread->_pTaskArg2 = 0;
		LQ_INSERT_TAIL(&pPool->_pIdleThreads, &pThread->_pNode);

		pThread->_hTask = CREATE_COND();
		pThread->_hHandle = (HANDLE)_beginthreadex(0, 0, workThread, pThread, 0, 0);
		i++;
	}
	_pThreadpool = pPool;
	return 1;
}



void releaseThreadPool()
{
	deleteThreads(_pThreadpool->_nIdleSize);
	Threadpool *pThreadpool = _pThreadpool;
	_pThreadpool = 0;

	sizet i = 0;
	LOCK(pThreadpool->_lockBusyThreads);
	sizet nBusySize = pThreadpool->_nBusySize;
	while(i < nBusySize)
	{
		S* pNode = LQ_HEAD(&pThreadpool->_pBusyThreads);
		LQ_REMOVE(pNode);
		Thread* pThread = LQ_DATA(pNode, Thread, _pNode);
		pThread->_bWorking = 0;
		SIGNAL(pThread->_hTask);

		WaitForSingleObject(pThread->_hHandle, INFINITE);
		CloseHandle(pThread->_hHandle);
		
		free(pThread);
	}
	pThreadpool->_nBusySize = 0;
	UNLOCK(_pThreadpool->_lockBusyThreads);
	DES_LOCK(pThreadpool->_lockBusyThreads);
	DES_LOCK(pThreadpool->_lockIdleThreads);
	DES_COND(pThreadpool->_hIdleCond);

	free(pThreadpool);
}



void pushTask(void (*pfTask)(void*,void*), void* pArg, void* pArg2)
{
	if(!_pThreadpool) return;
	if(!pfTask) return;

	if(_pThreadpool->_nMaxSize <= _pThreadpool->_nBusySize)
		WAIT(_pThreadpool->_hIdleCond);
	
	LOCK(_pThreadpool->_lockIdleThreads);
	bool bEmpty = LQ_ISEMPTY(&_pThreadpool->_pIdleThreads);
	UNLOCK(_pThreadpool->_lockIdleThreads);
	if(bEmpty) WAIT(_pThreadpool->_hIdleCond);

	LOCK(_pThreadpool->_lockIdleThreads);
	S* pNode = (LQ_NEXT(&_pThreadpool->_pIdleThreads));
	LQ_REMOVE(pNode);
	_pThreadpool->_nIdleSize--;
	UNLOCK(_pThreadpool->_lockIdleThreads);

	//将线程移动到繁忙线程链表中
	LOCK(_pThreadpool->_lockBusyThreads);
	LQ_INSERT_TAIL(&_pThreadpool->_pBusyThreads, pNode);
	_pThreadpool->_nBusySize++;
	UNLOCK(_pThreadpool->_lockBusyThreads);

	Thread* pThread = LQ_DATA(pNode, Thread, _pNode);
	pThread->_pfTask = pfTask;
	pThread->_pTaskArg = pArg;
	pThread->_pTaskArg2 = pArg2;
	//唤醒线程开始工作
	SIGNAL(pThread->_hTask);

	if(_pThreadpool->_nIdleSize < _pThreadpool->_nAvailLow)
    {
		if((_pThreadpool->_nTotalSize + _pThreadpool->_nInitSize - _pThreadpool->_nIdleSize) < _pThreadpool->_nMaxSize)
			createThreads(_pThreadpool->_nInitSize - _pThreadpool->_nIdleSize);
		else
			createThreads(_pThreadpool->_nMaxSize - _pThreadpool->_nTotalSize);
    }
}