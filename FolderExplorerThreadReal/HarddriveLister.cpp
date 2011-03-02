#include "HarddriveLister.h"

#include <Windows.h>
#include <iostream>

using namespace std;

HarddriveLister::HarddriveLister()
{
}


HarddriveLister::~HarddriveLister()
{
}
void HarddriveLister::list()
{
	DWORD ret = GetLogicalDrives();
	unsigned int i = 0;
	cout<<(char)ret<<endl;
}