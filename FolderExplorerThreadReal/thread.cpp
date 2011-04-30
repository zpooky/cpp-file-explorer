#include "Thread.h"

using namespace std;

/**PUBLIC CONSTRUCTS**/
Thread::Thread()
{
	this->xx = 0;
}
/**PUBLIC OPERATORS**/
/*void Thread::operator delete(void *t)
{
	if(t != NULL){
		cout<<"asdasdaas"<<endl;
		Thread *th = (Thread*)t;
		th->exit();
		delete th;
		th = NULL;
	}
}*/
/**PUBLIC DESTRUCT**/
Thread::~Thread()
{
}
/**PUBLIC STATIC FUNCTIONS**/
/**PUBLIC FUNCTIONS**/
void Thread::start()
{
	this->TID = _beginthreadex(NULL,0,ThreadFunc,(void*)this,0,&this->xx);
}
void Thread::notify()
{//ready

}
void Thread::wait()
{//sleep

}
void Thread::exit(){
	CloseHandle((HANDLE)this->TID);
}
void Thread::exitAll(){
	ExitProcess(1);//close main Thread also...
}
bool Thread::isThreaded(){
	DWORD status;
	if(!GetExitCodeThread((HANDLE)this->TID,&status)){
		return true;//fix perhaps count up when max reashed kill Thread and return false
	}
	return status == STILL_ACTIVE ? true : false;
}
void Thread::waitToFinish()
{
	WaitForSingleObject((HANDLE)this->TID,INFINITE);
}
/**PRIVATE FUNCTIONS**/
unsigned int WINAPI Thread::ThreadFunc(void *t)
{
	cout<<"1"<<endl;
	Thread *th = (Thread*)t;
	cout<<"2"<<endl;
	th->life();
	cout<<"3"<<endl;
	//_endthreadex(th->TID);
	//CloseHandle((HANDLE)th->TID);
	return 0;
}
/**PROTECTED FUNCTIONS**/
void Thread::life()
{
	cout<<"Thread with no life code!"<<endl;
}