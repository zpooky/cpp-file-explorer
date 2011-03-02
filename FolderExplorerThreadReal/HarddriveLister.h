#ifndef _SP_HARDDRIVELISTER_H_
#define _SP_HARDDRIVELISTER_H_

#pragma once

#include "stdafx.h"

#include <exception>

using namespace std;

class HarddriveLister
{
public:
	HarddriveLister();
	~HarddriveLister();
	void list() throw(exception);
};
#endif