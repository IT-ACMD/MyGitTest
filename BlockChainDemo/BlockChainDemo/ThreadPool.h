//
//  ThreadPool.h
//  Create by lousin on 2018/12/1.
//

#pragma once
#ifndef __ThreadPool_h__
#define __ThreadPool_h__
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int initThreadpool(sizet nSize);

void destroyThreadpool();

void pushTask(void (*)(void*,void*), void*, void*);

#endif