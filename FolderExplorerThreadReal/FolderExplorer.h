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

enum FileAttribute{
ATTRIBUTE_ARCHIVE = 32,
ATTRIBUTE_COMPRESSED = 2048,
ATTRIBUTE_DEVICE = 64,
ATTRIBUTE_DIRECTORY = 16,
ATTRIBUTE_ENCRYPTED = 16384,
ATTRIBUTE_HIDDEN = 2,
ATTRIBUTE_NORMAL = 128,
ATTRIBUTE_NOT_CONTENT_INDEXED = 8192,
ATTRIBUTE_OFFLINE = 4096,
ATTRIBUTE_READONLY = 1,
ATTRIBUTE_REPARSE_POINT = 1024,
ATTRIBUTE_SPARSE_FILE = 512,
ATTRIBUTE_SYSTEM = 4,
ATTRIBUTE_TEMPORARY = 256,
ATTRIBUTE_VIRTUAL = 65536
};

struct EXP_FILE_DATA
{
	wstring fileName;
	wstring filePath;
	unsigned int size;
	wstring lastWriteTime;
	bool isFolder;
	DWORD dwFileAttributes;
	FileAttribute mFileAttribute;
	EXP_FILE_DATA()
	{
		size = 0;
		isFolder = false;
	}
};

class FolderExplorer
{
private:
	//PATH
	wstring plainPath;
	wchar_t *path;
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