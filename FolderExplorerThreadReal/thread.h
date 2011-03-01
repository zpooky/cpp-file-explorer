#ifndef _SP_THREAD_H
#define _SP_THREAD_H

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <process.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <exception>

#include "stdafx.h"

using namespace std;

class thread
{
public:
	/**PUBLIC CONSTRUCTS**/
	thread();
	/**PUBLIC OPERATORS**/
	//void operator delete(void *t);
	/**PUBLIC DESTRUCT**/
	virtual ~thread();
	/**PUBLIC STATIC FUNCTIONS**/
	/**PUBLIC VARIABLES**/
	uintptr_t TID;
	/**PUBLIC FUNCTIONS**/
	void start();
	void notify();
	void wait();
	void exit();
	void exitAll();
	bool isActive();
private:
	/**PRIVATE STATIC VARIABLES**/
	/**PRIVATE VARIABLES**/
	unsigned int xx;
	/**PRIVATE FUNCTIONS**/
	/**PRIVATE STATIC FUNCTIONS**/
	static unsigned int WINAPI ThreadFunc(void *t);
protected:
	/**PROTECTED FUNCTIONS**/
	virtual void life();
	/**PROTECTED VARIABLES**/
	//uintptr_t TID;
};
#endif