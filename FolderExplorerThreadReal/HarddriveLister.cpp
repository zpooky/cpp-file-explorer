#include "HarddriveLister.h"

#include <direct.h>
#include <tchar.h>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
std::string trim_right ( const std::string & source ,const std::string & t = " " )
{
	std::string str = source;
	return str.erase ( str.find_last_not_of ( t ) + 1 ) ;
}
std::string trim_left ( const std::string & source ,const std::string & t = " " )
{
std::string str = source;
return str.erase ( 0 , source.find_first_not_of ( t ) ) ;
}
std::string trim ( const std::string & source ,const std::string & t = " " )
{
	std::string str = source;
	return trim_left ( trim_right ( str , t ) , t ) ;
}
HarddriveLister::HarddriveLister()
{
	this->mDriveLetter = new vector<wstring>();
	this->mBaseDriveLetter = new vector<wstring>();
	this->mDeviceList = new std::list<Device>();
}

HarddriveLister::~HarddriveLister()
{
	if(this->mBaseDriveLetter != NULL)
		delete this->mBaseDriveLetter;
	if(this->mDriveLetter != NULL)
		delete this->mDriveLetter;
	if(this->mDeviceList != NULL)
		delete this->mDeviceList;
}
std::list<Device> HarddriveLister::list()
{
	try{
	this->getDriveLetters();
	this->getDiskInfo();
	cout<<"-------------------------------"<<endl;
	this->getVolumeInformation();
	} catch(exception e){
		cout<<e.what()<<endl;
	}
	return *this->mDeviceList;
}
void HarddriveLister::getDiskInfo()
{
	DWORD bufferSize = 1024;
	TCHAR *buffer = new TCHAR[bufferSize];
	for(size_t i=0;i<this->mBaseDriveLetter->size();++i){
		this->queryDosDevice(this->mBaseDriveLetter->at(i).c_str(),(LPWSTR)buffer,bufferSize);
		printf("The DOS device name for %S is: ",this->mBaseDriveLetter->at(i).c_str());
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
	delete[]buffer;
}

void HarddriveLister::getDriveLetters()//working.
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
				int n = ::sprintf_s(charArr,"%S",(char *)szDrive);
				printf("%S", (char *)szDrive);
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

void HarddriveLister::setDisk(const char *str)//working.
{
	string tmpString = trim(str);
	wstring tmp = this->convert(tmpString.c_str());
	this->mDriveLetter->push_back(tmp);
	this->mBaseDriveLetter->push_back(tmp.substr(0,2));
}

wstring HarddriveLister::convert(const char *str)//working.
{
    size_t origsize = strlen(str) + 1;
    const size_t newsize = 5;
    size_t convertedChars = 0;
    wchar_t wcstring[newsize];
    ::mbstowcs_s(&convertedChars, wcstring, origsize, str, _TRUNCATE);
	wstring tmpReturnStr(wcstring,convertedChars);
	wchar_t buffer[4] = {0};
	errno_t error = wcscpy_s(buffer,4,tmpReturnStr.c_str());
	if(error != 0){
		cout<<"false"<<endl;
	}
	wcsncat_s(buffer,4,L"\\",1);
	wstring returnString(buffer,4);
	return returnString;
}
void HarddriveLister::compile()
{

}
void HarddriveLister::getVolumeInformation()
{/*C:\\*/
	for(size_t i=0;i<this->mDriveLetter->size();++i){
		TCHAR volumeName[MAX_PATH+1] = {0};
		TCHAR fileSystemName[MAX_PATH+1] = {0};
		DWORD serialNumber = 0;
		DWORD maxComponentLen = 0;
		DWORD fileSystemFlags = 0;
		if(::GetVolumeInformation(this->mDriveLetter->at(i).c_str(),volumeName,MAX_PATH+1,&serialNumber,&maxComponentLen,&fileSystemFlags,fileSystemName,MAX_PATH+1)){
			wcout<<L"Disk: '"<<this->mDriveLetter->at(i).c_str()<<"'"<<endl;
			_tprintf(_T("Volume Name: %s\n"), volumeName);
			_tprintf(_T("Serial Number: %lu\n"), serialNumber);
			_tprintf(_T("File System Name: %s\n"), fileSystemName);
			_tprintf(_T("Max Component Length: %lu\n"), maxComponentLen);
			cout<<"FileSystem Flags: "<<fileSystemFlags<<endl;
			DriveType driveType = this->getDriveType(this->mBaseDriveLetter->at(i).c_str());
			Device device = this->assign(this->mDriveLetter->at(i)[0],this->mDriveLetter->at(i).c_str(),volumeName,serialNumber,fileSystemName,driveType);
			this->mDeviceList->push_back(device);
		} else {
			wcout<<L"False: '"<<this->mDriveLetter->at(i).c_str()<<"'"<<endl;
			printf("Error: %d\n",::GetLastError());
		}
		cout<<"---"<<endl;
	}
}
Device HarddriveLister::assign(wchar_t driveLetter,const wchar_t *root,wchar_t *label,DWORD serial,wchar_t *fileSystem,DriveType driveType){
	Device device;
	device.diskLetter = driveLetter;
	errno_t error = wcscpy_s(device.label,MAX_PATH,label);
	if(error != 0){
		cout<<"false"<<endl;
	}
	error = wcscpy_s(device.root,4,root);
	if(error != 0){
		cout<<"false"<<endl;
	}
	device.serial = serial;
	device.deviceType = LOCAL_HARDDRIVE;//default
	if(fileSystem == L"NTFS"){
		device.fileSystem = NTFS;
	} else {
		device.fileSystem = FAT32;
	}
	device.driveType = driveType;
	return device;
}

bool HarddriveLister::queryDosDevice(LPCWSTR deviceName,LPWSTR buffer,DWORD &bufferSize)//working.
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
	for(size_t i=0;i<result;++i){
		cout<<buffer[i];
	}
	return true;
}

DriveType HarddriveLister::getDriveType(const wchar_t *driveLetter)
{
	return (DriveType)GetDriveType(driveLetter);
}
