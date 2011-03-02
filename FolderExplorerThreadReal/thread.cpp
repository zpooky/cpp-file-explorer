#include "thread.h"

using namespace std;

/**PUBLIC CONSTRUCTS**/
thread::thread()
{
}
/**PUBLIC OPERATORS**/
/*void thread::operator delete(void *t)
{
	if(t != NULL){
		cout<<"asdasdaas"<<endl;
		thread *th = (thread*)t;
		th->exit();
		delete th;
		th = NULL;
	}
}*/
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
	ExitProcess(1);//close main thread also...
}
bool thread::isThreaded(){
	DWORD status;
	if(!GetExitCodeThread((HANDLE)this->TID,&status)){
		return true;//fix perhaps count up when max reashed kill thread and return false
	}
	return status == STILL_ACTIVE ? true : false;
}
void thread::waitToFinish()
{
	WaitForSingleObject((HANDLE)this->TID,INFINITE);
}
/**PRIVATE FUNCTIONS**/
unsigned int WINAPI thread::ThreadFunc(void *t)
{
	thread *th = (thread*)t;
	th->life();
	//_endthreadex(th->TID);
	//CloseHandle((HANDLE)th->TID);
	return 0;
}
/**PROTECTED FUNCTIONS**/
void thread::life()
{
	cout<<"thread with no life code!"<<endl;
}