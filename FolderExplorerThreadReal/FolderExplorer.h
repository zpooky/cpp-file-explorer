#ifndef _FOLDEREXPLORER_H
#define _FOLDEREXPLORER_H

#pragma once

//http://msdn.microsoft.com/en-us/library/aa365740%28VS.85%29.aspx
//http://msdn.microsoft.com/en-us/library/ee332330%28v=VS.85%29.aspx
//wstring = UNICODE 
//wstring var = L"data";
//wcout to print

#include <string>
#include <windows.h>
#include <tchar.h> 
#include <wchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <vector>

using namespace std;

#ifndef _UNICODE
#define _UNICODE
#endif

struct EXP_FILE_DATA
{
	wstring FileName;
	unsigned int Size;
	wstring LastWriteTime;
	bool isFolder;
	DWORD dwFileAttributes;
	EXP_FILE_DATA()
	{
		Size = 0;
		isFolder = false;
		dwFileAttributes = NULL;
	}
};

class FolderExplorer
{
private:
	//PATH
	wstring plainPath;
	TCHAR *path;
	unsigned int nrOfPath;
	//FILTER NAME
	vector<wstring> filterData;
	//
	WIN32_FIND_DATA data;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	HANDLE handler;
	DWORD dwError;
	/**FUNCTIONS**/
	void convert(wstring path);
	bool pathLength();
	void prepare();
	void fetch();
	bool filter(wstring filename);
public:
	//OUTPUT FILE DATA
	vector<EXP_FILE_DATA> files;
	/**FUNCTIONS**/
	FolderExplorer();
	virtual ~FolderExplorer();
	bool open(wstring path);
	void addFilter(wstring name);
	int length()const;
};
#endif