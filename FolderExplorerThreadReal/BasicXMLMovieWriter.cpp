#include "BasicXMLMovieWriter.h"

using namespace std;

BasicXMLMovieWriter::BasicXMLMovieWriter(wofstream *out)
{
	this->mOutStream = out;
	this->header();
	this->mHeader = true;
}
BasicXMLMovieWriter::BasicXMLMovieWriter()
{
	this->mOutStream = NULL;
	this->mHeader = false;
}
BasicXMLMovieWriter::~BasicXMLMovieWriter()
{
	this->footer();
}
void BasicXMLMovieWriter::setStream(wofstream *out)
{
	this->mOutStream = out;
	if(!this->mHeader){
		this->header();
	}
}
void BasicXMLMovieWriter::header()
{
	if(this->mOutStream != NULL){
		*this->mOutStream<<L"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl;
		*this->mOutStream<<L"<list>"<<endl;
	}
}
void BasicXMLMovieWriter::element(const wchar_t *file,const wchar_t *path)
{
	if(this->mOutStream != NULL){
		*this->mOutStream<<L"  <movie>"<<endl;
		*this->mOutStream<<L"    <file type=\"name\">"<<file<<"</file>"<<endl;
		*this->mOutStream<<L"    <file type=\"path\">"<<path<<"</file>"<<endl;
		*this->mOutStream<<L"  </movie>"<<endl;
	}
}
void BasicXMLMovieWriter::footer()
{
	if(this->mOutStream != NULL){
		*this->mOutStream<<L"</list>";
	}
}