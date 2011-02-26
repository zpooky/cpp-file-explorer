#ifndef _SP_BASICXMLMOVIEWRITER_H_
#define _SP_BASICXMLMOVIEWRITER_H_

#pragma once

#include <string>
#include <iostream>

using namespace std;

class BasicXMLMovieWriter
{
private:
	wofstream *mOutStream;
public:
	BasicXMLMovieWriter(wofstream *out);
	~BasicXMLMovieWriter();
	void header();
	void element(const wchar_t *file,const wchar_t *path);
	void footer();
};
#endif