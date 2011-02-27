#include "BasicXMLMovieWriter.h"

using namespace std;

BasicXMLMovieWriter::BasicXMLMovieWriter(wofstream *out)
{
	this->mOutStream = out;
	this->header();
}
BasicXMLMovieWriter::~BasicXMLMovieWriter()
{
	this->footer();
}
void BasicXMLMovieWriter::header()
{
	*this->mOutStream<<L"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl;
	*this->mOutStream<<L"<list>"<<endl;
}
void BasicXMLMovieWriter::element(const wchar_t *file,const wchar_t *path)
{
	*this->mOutStream<<L"  <movie>"<<endl;
	*this->mOutStream<<L"    <file type=\"name\">"<<file<<"</file>"<<endl;
	*this->mOutStream<<L"    <file type=\"path\">"<<path<<"</file>"<<endl;
	*this->mOutStream<<L"  </movie>"<<endl;
}
void BasicXMLMovieWriter::footer()
{
	*this->mOutStream<<L"</list>";
}