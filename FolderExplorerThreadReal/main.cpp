#include <iostream>
#include <time.h>

#include "MovieTraverser.h"

using namespace std;

int main(){
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	wchar_t* arr[] = {L"c:\\",L"d:\\"};
	MovieTraverser *mt[2];
	time_t start = clock();
	for(int i=0;i<2;++i){
		mt[i] = new MovieTraverser(arr[i]);
		mt[i]->start();
	}
	bool verify = true;
	/*while(verify){
		verify = false;
		for(int i=0;i<2;++i){
			if(mt[i] != NULL){
				if(!mt[i]->isThreaded()){
					delete mt[i];
					mt[i] = NULL;
				} else {
					verify = true;
				}
			}
		}
	}*/
	time_t end = clock();
	time_t timer = end-start;
	cout<<"time:"<<(double)timer / ((double)CLOCKS_PER_SEC)<<endl;
	system("pause");
	return 0;
}