#ifndef _SP_BASICXMLMOVIEWRITER_H_
#define _SP_BASICXMLMOVIEWRITER_H_

#pragma once

#include "stdafx.h"

#include <wchar.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BasicXMLMovieWriter
{
private:
	wofstream *mOutStream;
	bool mHeader;
public:
	BasicXMLMovieWriter(wofstream *out);
	BasicXMLMovieWriter();
	~BasicXMLMovieWriter();
	void setStream(wofstream *out);
	void header();
	void element(const wchar_t *file,const wchar_t *path);
	void footer();
};
#endif