#include "FolderExplorer.h"
#include <iostream>

using namespace std;
//@TODO FIX EXPAND
FolderExplorer::FolderExplorer()
{
	//PATH
	this->path = NULL;
	this->nrOfPath = 0;
	//
	this->handler = INVALID_HANDLE_VALUE;
}

FolderExplorer::~FolderExplorer()
{
	//if(this->path != NULL)
	//	delete[]this->path;
}
bool FolderExplorer::open(wstring path)
{
	this->plainPath = path;
	this->convert(path);
	if(this->pathLength()){
		this->prepare();
		this->handler = FindFirstFile(this->path,&this->data);
		if(this->handler != INVALID_HANDLE_VALUE){
			this->files.clear();
			this->fetch();
			return true;
		} else {
			return false;
		}
	}
	return false;
}
void FolderExplorer::addFilter(wstring name)
{
	this->filterData.push_back(name);
}
int FolderExplorer::length() const
{
	return this->files.size();
}
/**PRIVATE FUNCTIONS**/
void FolderExplorer::convert(wstring dir)
{
	//@TODO this two lines result in a crash
	//if(this->path != NULL)
	//	delete[]this->path;
	//if unicode is TCHAR is wchar_t. find out a way to make that so "new" do not have to be called.c string
	//this->path = dir.c_str();
	this->path = new wchar_t[dir.size()+1];
	this->path[dir.size()] = 0;
	this->nrOfPath = dir.size();
	//As much as we'd love to, we can't use memcpy() because
	//sizeof(TCHAR)==sizeof(char) may not be true:
	for(unsigned int i=0;i<dir.size();++i){
		this->path[i] = dir[i];
	}
}
/**
* @DESC Check that the input path plus 3 is not longer than MAX_PATH.
*		Three characters are for the "\*" plus NULL appended
**/
bool FolderExplorer::pathLength()
{
	size_t length_of_arg;
	//GET THE LENGTH OF  INTO length_of_arg MAX_PATH is maximum length of  will return ok if shorter then max
	StringCchLength(this->path, MAX_PATH, &length_of_arg);
	return !(length_of_arg > (MAX_PATH-3));
}
void FolderExplorer::prepare()
{
	size_t last = wcslen(this->path);
	last = last-1 >= 0 ? last-1 : 0;
	if(this->path[last] != L'\\'){
		StringCchCat(this->path,MAX_PATH,TEXT("\\*"));
	} else {
		StringCchCat(this->path,MAX_PATH,TEXT("*"));
	}
}
void FolderExplorer::fetch()
{
	int i = 0,
		nrOfFiles = 0;
	wchar_t buffer[255] = {0};
	EXP_FILE_DATA obj;
	do{
		for(i=0;i<lstrlen(this->data.cFileName)&&i<255;++i){
			buffer[i] = wchar_t(this->data.cFileName[i]);
		}
		obj.fileName = wstring(buffer,i);
		if(this->filter(obj.fileName)){
			this->files.push_back(obj);
			this->files.at(nrOfFiles).filePath = this->path;
			this->files.at(nrOfFiles).isFolder = (this->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
			this->files.at(nrOfFiles).dwFileAttributes = this->data.dwFileAttributes;
			this->files.at(nrOfFiles).mFileAttribute = (FileAttribute)this->data.dwFileAttributes;
			++nrOfFiles;
		}
	}while(FindNextFile(this->handler,&this->data));
	FindClose(this->handler);
}
bool FolderExplorer::filter(wstring filename)
{
	for(int i=0;i<(int)this->filterData.size();++i){
		if(filename == this->filterData.at(i)){
			return false;
		}
	}
	return true;
}