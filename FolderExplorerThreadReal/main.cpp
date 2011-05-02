#include <iostream>
#include <time.h>

#include "MovieTraverser.h"
#include "HarddriveLister.h"
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
#include <tchar.h>
#include <cmath>
#include <list>

using namespace std;

/*
int main(){
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	HarddriveLister *harddriveLister = new HarddriveLister();
	list<Device> deviceList;
	try{
		deviceList = harddriveLister->list();
	} catch(exception e){
		cout<<e.what()<<endl;
	}
	delete harddriveLister;
	cout<<"-------_"<<endl;
	for(list<Device>::iterator it=deviceList.begin();it != deviceList.end();++it){
		//wcout<<L"x--x"<<endl;
		wcout<<it->diskLetter<<endl;
		wcout<<it->deviceType<<endl;
		wcout<<it->driveType<<endl;
		wcout<<it->fileSystem<<endl;
		wcout<<it->label<<endl;
		wcout<<it->serial<<endl;
 		wcout<<L"--"<<endl;
	}
	system("pause");
	return 0;
}*/

int main(){
	setlocale(LC_ALL,"swedish");
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	HarddriveLister *harddriveLister = new HarddriveLister();
	list<Device> deviceList;
	try{
		deviceList = harddriveLister->list();
	} catch(const exception e){
		cout<<e.what()<<endl;
		return 0;
	}
	delete harddriveLister;
	MovieTraverser **mt = new MovieTraverser*[deviceList.size()];
	time_t start = clock();
	size_t i = 0;
	//for(list<Device>::iterator it=deviceList.begin();it != deviceList.end();++it){
	//	mt[i] = new MovieTraverser(it->root);
	//	mt[i]->start();
	//	++i;
	//}
	mt[0] = new MovieTraverser(L"C:\\");
		mt[0]->start();
		mt[0]->waitToFinish();
			delete mt[0];
	//for(size_t a=0;a<deviceList.size();++a){
	//	if(mt[a] != NULL){
	//		mt[a]->waitToFinish();
	//		delete mt[a];
	//		mt[a] = NULL;
	//	}
	//}
	time_t end = clock();
	delete[]mt;
	time_t timer = end-start;
	cout<<"time:"<<(double)timer / ((double)CLOCKS_PER_SEC)<<endl;
	system("pause");
	return 0;
}
/*
int main(){
	FolderExplorer *fe = new FolderExplorer();
	unsigned int i = 0;
	while(1){
		//cout<<"Iteration:"<<i++<<endl;
		cout<<"try to open path"<<endl;
		if(fe->open(L"D:\\едц")){
		cout<<"vector size:"<<fe->files.size()<<endl;
			for(size_t i=0;i<fe->files.size();++i){
				wcout<<fe->files.at(i).fileName<<endl;
			}
		}
	}
	delete fe;
	return 0;
}*/