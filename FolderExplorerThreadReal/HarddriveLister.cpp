#include "HarddriveLister.h"

#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

HarddriveLister::HarddriveLister()
{
}


HarddriveLister::~HarddriveLister()
{
}
void HarddriveLister::list() throw(exception)
{
	TCHAR szDrive[] = _T(" A:");
	DWORD logicalDrives = GetLogicalDrives();
	if(logicalDrives == 0){
		throw "Unable to read drives.";
	} else {
		while(logicalDrives){
			// Use the bitwise AND, 1–available, 0-not available
			if(logicalDrives & 1){
				printf("%S", (const char *)szDrive);
				string str((const char *)szDrive);
				cout<<str.c_str();
			}
			// increment, check next drive
			++szDrive[1];
			// shift the bitmask binary right
			logicalDrives >>= 1;
		}
	}
}