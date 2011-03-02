#include <iostream>
#include <time.h>

#include "MovieTraverser.h"
#include "HarddriveLister.h"
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
#include <tchar.h>
#include <cmath>

using namespace std;


int main(){
	HarddriveLister *harddriveLister = new HarddriveLister();
	harddriveLister->list();
	delete harddriveLister;
	system("pause");
	return 0;
}

/*int main(){
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	wchar_t* arr[] = {L"c:\\",L"d:\\"};
	MovieTraverser *mt[2] = {NULL,NULL};
	time_t start = clock();
	for(int i=0;i<2;++i){
		mt[i] = new MovieTraverser(arr[i]);
		mt[i]->start();
	}
	mt[1]->waitToFinish();
	delete mt[1];
	mt[0]->waitToFinish();
	delete mt[0];
	time_t end = clock();
	time_t timer = end-start;
	cout<<"time:"<<(double)timer / ((double)CLOCKS_PER_SEC)<<endl;
	system("pause");
	return 0;
}**/