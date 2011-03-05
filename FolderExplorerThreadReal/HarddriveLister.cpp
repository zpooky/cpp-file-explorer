#include "HarddriveLister.h"

#include <direct.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <algorithm>

using namespace std;

HarddriveLister::HarddriveLister()
{
	this->mDriveLetter = new wstring[4];
	this->mBaseDriveLetter = new wstring[4];
	this->mBaseDriveLetterSize = 0;
}

HarddriveLister::~HarddriveLister()
{
	if(this->mBaseDriveLetter != NULL)
		delete[]this->mBaseDriveLetter;
	if(this->mDriveLetter != NULL)
		delete[]this->mDriveLetter;
}
void HarddriveLister::list()
{
	this->getDriveLetters();
	/*for(size_t i=0;i<this->test.size();++i){
		cout<<this->test.at(i);
	}*/
	//this->getDiskInfo();
	this->getVolumeInformation();
}
void HarddriveLister::getDiskInfo()
{
	DWORD bufferSize = 1024;
	TCHAR *buffer = new TCHAR[bufferSize];
	for(size_t i=0;i<this->mBaseDriveLetterSize;++i){
		this->queryDosDevice(this->mBaseDriveLetter[i].c_str(),(LPWSTR)buffer,bufferSize);
		printf("The DOS device name for %S is: ", this->mBaseDriveLetter[i].c_str());
		size_t a = 0;
		while(buffer[a] != NULL && buffer[a+1] != NULL){
			if(buffer[a] != NULL){
				wcout<<buffer[a];
			} else {
				cout<<endl;
			}
			++a;
		}
		printf("\n");
	}
}

void HarddriveLister::getDriveLetters()
{
	TCHAR szDrive[] = _T(" A:");
	char charArr[5];
	DWORD logicalDrives = ::GetLogicalDrives();
	if(logicalDrives == 0){
		throw "Unable to read drives.";
	} else {
		//throw "test";
		while(logicalDrives){
			// Use the bitwise AND, 1–available, 0-not available
			if(logicalDrives & 1){
				int n = ::sprintf_s(charArr,"%S",(const char *)szDrive);
				string str(charArr,n);
				this->setDisk(str.c_str());
			}
			// increment, check next drive
			++szDrive[1];
			// shift the bitmask binary right
			logicalDrives >>= 1;
		}
	}
}

void HarddriveLister::setDisk(const char *str)
{
	this->test.push_back(str);
	wstring tmpStr = this->convert(str);
    remove(tmpStr.begin(),tmpStr.end(),' ');
	this->mBaseDriveLetter[this->mBaseDriveLetterSize++] = tmpStr;
	/*cout<<"__"<<endl;
	for(size_t i=0;i<this->mBaseDriveLetterSize;++i){
		wcout<<i<<" '"<<this->mBaseDriveLetter[i]<<"'"<<endl;
		continue;
	}
	cout<<"__"<<endl;*/
}

wstring HarddriveLister::convert(const char *str)
{
    size_t origsize = strlen(str) + 1;
    const size_t newsize = 5;
    size_t convertedChars = 0;
    wchar_t wcstring[newsize];
    ::mbstowcs_s(&convertedChars, wcstring, origsize, str, _TRUNCATE);
	wstring retStr(wcstring,convertedChars);
	return retStr;
}
void HarddriveLister::compile()
{

}
void HarddriveLister::getVolumeInformation()
{
	for(size_t i=0;i<this->mBaseDriveLetterSize;++i){
		TCHAR volumeName[MAX_PATH+1] = {0};
		TCHAR fileSystemName[MAX_PATH+1] = {0};
		DWORD serialNumber = 0;
		DWORD maxComponentLen = 0;
		DWORD fileSystemFlags = 0;
		if (GetVolumeInformation(this->mBaseDriveLetter[i].c_str(),volumeName,MAX_PATH+1,&serialNumber,&maxComponentLen,&fileSystemFlags,fileSystemName,MAX_PATH+1)){
			_tprintf(_T("Volume Name: %s\n"), volumeName);
			_tprintf(_T("Serial Number: %lu\n"), serialNumber);
			_tprintf(_T("File System Name: %s\n"), fileSystemName);
			_tprintf(_T("Max Component Length: %lu\n"), maxComponentLen);
			cout<<"FileSystem Flags: "<<fileSystemFlags<<endl;
		} else {
			wcout<<L"False: "<<this->mBaseDriveLetter[i].c_str()<<endl;
		}
	}
}
bool HarddriveLister::queryDosDevice(LPCWSTR deviceName,LPWSTR buffer,DWORD &bufferSize)
{
	if(deviceName == NULL){
		return false;
	}
	if(buffer == NULL){
		bufferSize = 1024;
		buffer = new TCHAR[bufferSize];
	}
	bool cont = true;
	DWORD result = 0,
		  error = 0;
	while(cont){
		// If the function succeeds, the return value is the number of TCHARs stored
		// into the buffer pointed to by lpTargetPath. If the function fails, the return
		// value is zero. To get extended error information, call GetLastError.
		result = ::QueryDosDevice(deviceName,buffer,bufferSize);
		if(result == 0){
			error = ::GetLastError();
			if(error == ERROR_INSUFFICIENT_BUFFER){
				delete[]buffer;
				bufferSize *= 2;
				buffer = new TCHAR[bufferSize];
			} else {
				cont = false;
			}
		} else {
			cont = false;
		}
	}
	printf("QueryDosDevice() return value: %d, Error: %d\n", result, ::GetLastError());
	return true;
}