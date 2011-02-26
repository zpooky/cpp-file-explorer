#include "BasicXMLMovieWriter.h"

using namespace std;

BasicXMLMovieWriter::BasicXMLMovieWriter(wofstream *out)
{
	this->mOutStream = out;
}
BasicXMLMovieWriter::~BasicXMLMovieWriter()
{
}
void BasicXMLMovieWriter::header()
{
	*this->mOutStream<<"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl;
	*this->mOutStream<<"<list>"<<endl;
}
void BasicXMLMovieWriter::element(const wchar_t *file,const wchar_t *path)
{
	*this->mOutStream<<"  <movie>"<<endl;
	*this->mOutStream<<"    <file type=\"name\">"<<file<<"</file>"<<endl;
	*this->mOutStream<<"    <file type=\"path\">"<<path<<"</file>"<<endl;
	*this->mOutStream<<"  </movie>"<<endl;
}
void BasicXMLMovieWriter::footer()
{
	*this->mOutStream<<"</list>";
}