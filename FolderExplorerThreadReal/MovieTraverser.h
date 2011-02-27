#ifndef _SP_MOVIETRAVERSER_H_
#define _SP_MOVIETRAVERSER_H_

#pragma once

#include <string>
#include <fstream>
#include <wchar.h>
#include <vector>
 
#include "stdafx.h"
#include "thread.h"
#include "FolderExplorer.h"
#include "BinarySemaphore.h"

using namespace std;

class MovieTraverser : public thread
{
private:
	/**VARIABLES**/
	wstring root;
	wstring curPath;
	wstring curFolder;
	wstring prevFolder;
	bool isBack;
	FolderExplorer *fe;
	vector<wchar_t*> movieExt;
	/**STATIC VARIABLES**/
	static int initCount;
	static BinarySemaphore *sem;
	static wofstream *out;
	/**FUNCTIONS**/
	void initiate(wchar_t *root);
	bool visit(const wchar_t *file,const wchar_t *path);
	bool checkExt(const wchar_t *file);
	bool search(wstring &str);
	wstring getExt(const wstring &file);
	void backFolder();
	/**STATIC FUNCTIONS**/
	static void init();
	static void deInit();
	static void write(const wchar_t *file,const wchar_t *path);
	static void writeXML(const wchar_t *file,const wchar_t *path);
protected:
	void life();
public:
	/**FUNCTIONS**/
	MovieTraverser();
	MovieTraverser(wchar_t *root);
	~MovieTraverser();
	void setRoot(wchar_t *root);
};

#endif