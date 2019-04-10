#pragma once

/*includes*/


/* basic data type definition ----------*/
#ifndef bytet
#define bytet   unsigned char
#endif
#ifndef sizet
#define sizet   unsigned int
#endif
/* --------------------------------*/



/* lock -------------------------------------------------------- */
#define CSLOCK             CRITICAL_SECTION

#if (_WIN32_WINNT >= 0x0403)
	#define CREATE_LOCK(x) InitializeCriticalSectionAndSpinCount(&x,4000);
#else
	#define CREATE_LOCK(x) InitializeCriticalSection(&x);
#endif

#define DES_LOCK(x)        DeleteCriticalSection(&x)
#define LOCK(x)            EnterCriticalSection(&x)
#define UNLOCK(x)          LeaveCriticalSection(&x)



/* condition --------------------------------------------------- */
#define HCOND              HANDLE
#define CREATE_COND()      CreateEvent(NULL,TRUE,FALSE,NULL)
#define DES_COND(x)        CloseHandle(x)
#define WAIT(x)            do{ WaitForSingleObject(x,INFINITE); ResetEvent(x); }while(0)
#define SIGNAL(x)          SetEvent(x)



/* linked list and queue : LQ ---------------------------------- */

typedef void* S[2];
#define LQ_NEXT(s)       (*(S **) &((*(s))[0]))
#define LQ_PREV(s)       (*(S **) &((*(s))[1]))
#define LQ_PREV_NEXT(s)  (LQ_NEXT(LQ_PREV(s)))
#define LQ_NEXT_PREV(s)  (LQ_PREV(LQ_NEXT(s)))

#define LQ_INIT(s) do{										\
	LQ_NEXT(s) = (s);										\
	LQ_PREV(s) = (s);										\
}while(0)

#define LQ_ISEMPTY(s)										\
	((const S*) (s) == (const S*) LQ_NEXT(s))

#define LQ_FOREACH(s,h)										\
	for((s) = LQ_NEXT(h); (s) != (h); (s) = LQ_NEXT(s))

#define LQ_HEAD(s)                          				\
	(LQ_NEXT(s))

#define LQ_INSERT_HEAD(s,n) do{            					\
    LQ_NEXT(n) = LQ_NEXT(s);                				\
    LQ_PREV(n) = (s);                     					\
    LQ_NEXT_PREV(n) = (n);                					\
    LQ_NEXT(s) = (n);                     					\
}while(0)

#define LQ_INSERT_TAIL(s,n) do{         					\
	LQ_NEXT(n) = (s);                       				\
	LQ_PREV(n) = LQ_PREV(s);                				\
	LQ_PREV_NEXT(n) = (n);                  				\
	LQ_PREV(s) = (n);                       				\
}while(0)

#define LQ_REMOVE(n) do{                    				\
	LQ_PREV_NEXT(n) = LQ_NEXT(n);           				\
	LQ_NEXT_PREV(n) = LQ_PREV(n);           				\
}while(0)

#define LQ_DATA(n,t,f)                      				\
	((t*)((bytet*)(n) - offsetof(t, f)))



/* Binary ------------------------------------------------------ */
#define B_READ(p,i,t,d) do{                                 \
	(d) = *((t*)((p) + (i)));								\
	(i) += sizeof(t);										\
}while(0)

#define B_READLONG(p,i,d) do{								\
	B_READ(p, i, sizet, *(((sizet*)(&d))+1));				\
	B_READ(p, i, sizet, *((sizet*)(&d)));					\
}while(0)

#define B_READBYTES(p,i,d,s) do{							\
	memcpy((void*)(d), (const void*)((p)+(i)), (s));		\
	(i) += (s);												\
}while(0)

#define B_READSTR(p,i,d) do{								\
	sizet s = 0;											\
	B_READ(p, i, sizet, s);									\
	if(s <= 0) break;										\
	string str((char*)((p) + (i)), s);						\
	(d) = str;												\
	(i) += s;												\
}while(0)

#define B_WRITE(p,i,t,d) do{								\
	*((t*)((p) + (i))) = (d);								\
	(i) += sizeof(t);										\
}while(0)

#define B_WRITELONG(p,i,d) do{								\
	B_WRITE(p, i, sizet, (((long long)d) >> (sizeof(sizet)*8)));\
	B_WRITE(p, i, sizet, (sizet)d);							\
}while(0)

#define B_WRITEBYTES(p,i,d,s) do{							\
	memcpy((void*)((p)+(i)), (const void*)(d), (s));		\
	(i) += (s);												\
}while(0)

#define B_WRITESTR(p,i,d) do{								\
	B_WRITE(p, i, sizet, d.size());							\
	if(d.size() > 0) break;									\
	B_WRITEBYTES(p, i, d.c_str(), d.size());				\
}while(0)