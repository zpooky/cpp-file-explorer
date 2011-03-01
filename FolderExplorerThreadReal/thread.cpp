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
	ExitProcess(1);
}
bool thread::isActive(){
	DWORD status;
	if(!GetExitCodeThread((HANDLE)this->TID,&status)){
		return true;
	}
	if(status == STILL_ACTIVE){
		cout<<"STILL_ACTIVE"<<endl;
	} else {
		cout<<"default: "<<status<<endl;
	}
	return status == STILL_ACTIVE ? true : false;
}
/**PRIVATE FUNCTIONS**/
unsigned int WINAPI thread::ThreadFunc(void *t)
{
	thread *th = (thread*)t;
	th->life();
	cout<<"life end"<<endl;
	//_endthreadex(th->TID);
	//CloseHandle((HANDLE)th->TID);
	return 0;
}
/**PROTECTED FUNCTIONS**/
void thread::life()
{
	cout<<"thread with no life code!"<<endl;
}