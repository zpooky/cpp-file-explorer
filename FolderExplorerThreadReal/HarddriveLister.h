#ifndef _SP_HARDDRIVELISTER_H_
#define _SP_HARDDRIVELISTER_H_

#pragma once

#include "stdafx.h"
#include <string>
#include <exception>
#include <list>
#include <vector>
#include <Windows.h>

using namespace std;

enum DeviceType{LOCAL_HARDDRIVE};
//http://msdn.microsoft.com/en-us/library/aa364939%28v=VS.85%29.aspx
//enum DriveType{DRIVE_UNKNOWN,DRIVE_NO_ROOT_DIR,DRIVE_REMOVABLE,DRIVE_FIXED,DRIVE_REMOTE,DRIVE_CDROM,DRIVE_RAMDISK};

struct Device
{
	wchar_t *label;
	wchar_t diskLetter;
	DWORD serialNumber;
	DeviceType deviceType;
	//DriveType driveType;
	//HARDDRIVE SPECIFIC?
	wchar_t *fileSystem;
};

class HarddriveLister
{
public:
	HarddriveLister();
	~HarddriveLister();
	void list() throw(exception);
private:
	wstring* mBaseDriveLetter;//list...
	size_t mBaseDriveLetterSize;
	//list<LPCWSTR> mBaseDriveLetter;
	wstring* mDriveLetter;
	vector<string> test;
	void getDiskInfo() throw(exception);
	void setDisk(const char *str);
	void getDriveLetters() throw(exception);
	wstring convert(const char *str);
	void compile();
	void getVolumeInformation();
	bool queryDosDevice(LPCWSTR deviceName,LPWSTR buffer,DWORD &bufferSize);
};
#endif