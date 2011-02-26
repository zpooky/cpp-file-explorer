#include "thread.h"

using namespace std;

/**PUBLIC CONSTRUCTS**/
thread::thread()
{
	this->threaded = false;
}
/**PUBLIC OPERATORS**/
/**PUBLIC DESTRUCT**/
thread::~thread()
{
}
/**PUBLIC STATIC FUNCTIONS**/
/**PUBLIC FUNCTIONS**/
void thread::start()
{
	this->TID = _beginthreadex(NULL,0,ThreadFunc,(void*)this,0,&this->xx);
}
void thread::notify()
{//ready

}
void thread::wait()
{//sleep

}
void thread::exit(){
	CloseHandle((HANDLE)this->TID);
}
void thread::exitAll(){
	ExitProcess(1);
}
bool thread::isThreaded(){
	return this->threaded;
}
/**PRIVATE FUNCTIONS**/
unsigned int WINAPI thread::ThreadFunc(void *t)
{
	thread *th = (thread*)t;
	th->threaded = true;
	th->life();
	th->threaded = false;
	 _endthreadex(0);
	return 0;
}
/**PROTECTED FUNCTIONS**/
void thread::life()
{
	cout<<"thread with no life code!"<<endl;
}