#ifndef _BINARY_SEMAPHORE_H_
#define _BINARY_SEMAPHORE_H_

#pragma once

#include <queue>

using namespace std;

class BinarySemaphore
{
private:
	queue<unsigned int> q;
	unsigned int status;
public:
	void signal();
	void wait(unsigned int PID);
	BinarySemaphore();
	~BinarySemaphore();
};
#endif