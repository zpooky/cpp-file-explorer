#ifndef _SP_MOVIETRAVERSERTHREAD_H
#define _SP_MOVIETRAVERSERTHREAD_H

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <string>
#include <wchar.h>
#include <fstream>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>

#include "FolderExplorer.h"
#include "BinarySemaphore.h"

using namespace std;

class movieTraverserThread
{
private:
	/**PRIVATE STATIC VARIABLES**/
	static unsigned int MAX_THREAD;
	static unsigned int CUR_THREADS;
	/**SEMAPHORE**/
	BinarySemaphore *sem;
	/**PRIVATE VARIABLES**/
	unsigned int *TID;
	wstring *root;
	int nrOf;
	wstring *curPath;
	wstring *curFolder;
	wstring *prevFolder;
	bool *isBack;
	wofstream *out;
	FolderExplorer *fe;
	vector<wstring> movieExt;
	/**PRIVATE FUNCTIONS**/
	void start(int length);
	void initiate(wstring* root,int length);
	bool visit(const wstring &input,int id);
	void write(const wstring &input,int id);
	bool checkExt(const wstring &input);
	wstring getExt(const wstring &input);
	void backFolder(int id);
	static unsigned int WINAPI ThreadFunc(void *p);
	void traverse(int id);
	bool compare(const wstring &str1,const wstring &str2);
public:
	/**PUBLIC CONSTRUCTS**/
	movieTraverserThread();
	movieTraverserThread(const wstring &input);
	movieTraverserThread(wstring *arr,int size);
	//movieTraverserThread(wstring arr[],int size);
	~movieTraverserThread();
	/**PUBLIC STATIC FUNCTIONS**/
	static void setMaxThread(int threads);
	/**PUBLIC FUNCTIONS**/
	void setRoot(const wstring &root);
	void traverse();
};

struct parameter {
	int id;
	movieTraverserThread *mtt;
	bool is_thread;
	parameter::parameter(){
		this->id = 0;
		this->mtt = NULL;
		this->is_thread = false;
	}
};

#endif