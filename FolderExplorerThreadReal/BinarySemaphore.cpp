#include "BinarySemaphore.h"


BinarySemaphore::BinarySemaphore()
{
	this->status = 0;
}


BinarySemaphore::~BinarySemaphore()
{
}

void BinarySemaphore::signal()
{
	if(!this->q.empty()){
		unsigned int PID = this->q.front();
		this->q.pop();
		//ResumeThread(PID);
	} else {
		this->status = 0;
	}
}
void BinarySemaphore::wait(unsigned int PID)
{
	if(this->status == 0){
		//test and set?
		this->status = 1;
	} else {
		//SuspendThread(PID);
		this->q.push(PID);
	}
}