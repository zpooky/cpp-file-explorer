#ifndef _SP_HARDDRIVELISTER_H_
#define _SP_HARDDRIVELISTER_H_

#pragma once

#include "stdafx.h"
#include <string>
#include <exception>
#include <list>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
using namespace std;

enum DeviceType{LOCAL_HARDDRIVE};
enum DriveType{DRIVETYPE_UNKNOWN,DRIVETYPE_NO_ROOT_DIR,DRIVETYPE_REMOVABLE,DRIVETYPE_FIXED,DRIVETYPE_REMOTE,DRIVETYPE_CDROM,DRIVETYPE_RAMDISK};
//http://msdn.microsoft.com/en-us/library/aa364939%28v=VS.85%29.aspx
enum FileSystem{NTFS,FAT32};

struct Device
{
	wchar_t label[MAX_PATH+1];
	wchar_t root[4];
	wchar_t diskLetter;
	DWORD serial;
	DeviceType deviceType;
	DriveType driveType;
	//HARDDRIVE SPECIFIC?
	FileSystem fileSystem;
};

class HarddriveLister
{
public:
	HarddriveLister();
	~HarddriveLister();
	std::list<Device> list();
private:
	vector<wstring> *mBaseDriveLetter;
	vector<wstring> *mDriveLetter;
	std::list<Device> *mDeviceList;
	void getDiskInfo();
	void setDisk(const char *str);
	void getDriveLetters() throw(...);
	wstring convert(const char *str);
	void compile();
	void getVolumeInformation();
	bool queryDosDevice(LPCWSTR deviceName,LPWSTR buffer,DWORD &bufferSize);
	DriveType getDriveType(const wchar_t *driveLetter);
	Device assign(wchar_t driveLetter,const wchar_t *root,wchar_t *label,DWORD serial,wchar_t *fileSystem,DriveType driveType);
};
#endif