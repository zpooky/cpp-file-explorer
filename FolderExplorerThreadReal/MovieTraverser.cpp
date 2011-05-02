#include "movieTraverser.h"
#include <iostream>
#include <regex>

#include "spFunc.h"

using namespace std;
using namespace tr1;

int MovieTraverser::initCount = 0;
BinarySemaphore* MovieTraverser::mSem = new BinarySemaphore();
wofstream* MovieTraverser::mOut = new wofstream();
BasicXMLMovieWriter* MovieTraverser::mXMLWriter = new BasicXMLMovieWriter();

MovieTraverser::MovieTraverser() : Thread()
{
	this->fe = NULL;
	MovieTraverser::init();
	this->initiate(L"C:\\");
}
MovieTraverser::MovieTraverser(wchar_t *root) : Thread()
{
	this->fe = NULL;
	MovieTraverser::init();
	this->initiate(root);
}
MovieTraverser::~MovieTraverser()
{
	MovieTraverser::deInit();
	if(this->fe != NULL)
		delete this->fe;
}
void MovieTraverser::setRoot(wchar_t *root)
{
	this->root = root;
	this->curPath = this->root;
}
void MovieTraverser::life()
{
	vector<wstring> folder;
	this->curPath = this->root;
	bool cont = true;
	//cout<<"____________"<<endl;
	do{
		folder.clear();
		if(this->fe->open(this->curPath)){
			//
			//wcout<<L"'"<<L"curPath:"<<this->curPath<<L"'"<<endl;
			//wcout<<L"'"<<L"root:"<<this->root<<L"'"<<endl;
			//wcout<<L"'"<<L"prevPath:"<<this->prevFolder<<L"'"<<endl;
			//
			for(unsigned int i=0;i<this->fe->files.size();++i){
				////wcout<<this->fe->files.at(i).FileName<<" |"<<this->fe->files.at(i).isFolder<<"|"<<this->fe->files.at(i).dwFileAttributes<<endl;
				if(this->fe->files[i].dwFileAttributes == 18 || this->fe->files[i].dwFileAttributes == 22 || this->fe->files[i].dwFileAttributes == 48){
					////wcout<<"No:file/folder: "<<this->fe->files[i].filePath<<this->fe->files[i].fileName<<endl;
				} else
				if(this->fe->files[i].isFolder){
					folder.push_back(this->fe->files.at(i).fileName);
					//wcout<<L"'"<<L"folder:|"<<L"'"<<this->fe->files.at(i).filePath<<this->fe->files.at(i).fileName<<L"'"<<endl;
				} else 
				if(!this->isBack){
					//wcout<<L"file::"<<L"'"<<this->fe->files.at(i).fileName<<L"'"<<endl;
					this->visit(this->fe->files.at(i).fileName.c_str(),this->curPath.c_str());
				}
			}
			this->prevFolder = this->curPath;
			if(this->isBack){
				bool verify = true;
				for(unsigned int i=0;i<folder.size() && verify;++i){
					////cout<<"|"<<this->curFolder<<"| |"<<folder[i]<<"|"<<endl;
					if(this->curFolder == folder[i]){
						++i;
						if(i<folder.size()){
							this->isBack = false;
							this->curPath += folder[i]+L'\\';
							this->curFolder = folder[i];
						} else {
							this->isBack = true;
							if(this->curPath == this->root){
								cont = false;
							} else {
								this->backFolder();
							}
						}
						verify = false;
					}
				}
			} else
			if(!this->isBack){
				size_t i = 0;
				if(i<folder.size()){
					this->isBack = false;
					this->curPath += folder[i]+L'\\';
					this->curFolder = folder[i];
				} else {
					this->isBack = true;
					if(this->curPath == this->root){
						cont = false;
					} else {
						this->backFolder();
					}
				}
			}
		} else {
			//cout<<"__Fail__"<<endl;
			//wcout<<L"curPath:"<<this->curPath<<endl;
			//wcout<<L"root:"<<this->root<<endl;
			//cout<<"__"<<endl;
			cont = false;
		}
		//system("pause");
	}while(cont);
	//wcout<<endl<<L"done: "<<this->root<<endl;
}
/**FUNCTIONS**/
void MovieTraverser::initiate(wchar_t *root)
{
	root[wcslen(root)-1] != '\\' ? root+L'\\' : root;
	this->root = root;
	this->curPath = this->root;
	this->isBack = false;
	if(this->fe != NULL)//@TODO dont delete
		delete this->fe;
	this->fe = new FolderExplorer();
	this->fe->addFilter(L"..");
	this->fe->addFilter(L".");
	this->movieExt.push_back(L"avi");
	//this->movieExt.push_back(L"flv");
	this->movieExt.push_back(L"mkv");
	this->movieExt.push_back(L"mp4");
	this->movieExt.push_back(L"wmv");
	//this->movieExt.push_back(L"mov");
}
bool MovieTraverser::visit(const wchar_t *file,const wchar_t *path)
{
	if(this->checkExt(file)){
		MovieTraverser::mSem->wait(this->TID);
		MovieTraverser::writeXML(file,path);
		MovieTraverser::mSem->signal();
	}
	return true;
}
void MovieTraverser::write(const wchar_t *file,const wchar_t *path)
{
	*MovieTraverser::mOut<<file<<L"|"<<path<<file<<endl;
}
void MovieTraverser::writeXML(const wchar_t *file,const wchar_t *path)
{
	MovieTraverser::mXMLWriter->element(file,path);
}
bool MovieTraverser::checkExt(const wchar_t *file)
{
	wstring ext = this->getExt(file);
	/*if(file.substr((file.length()-ext.length()),file.length()-1) == ext){
	} else {
		//wcout<<file<<endl;
	}*/
	for(unsigned int i=0;i<movieExt.size();++i){
		if(ext == movieExt.at(i)){
			return true;
		}
	}
	return false;
}
bool MovieTraverser::search(wstring &str)
{//dont work. use wstring version
	regex rx("a");
	//return regex_match(str.begin(),str.end(),rx);
	return false;
}
wstring MovieTraverser::getExt(const wstring &file)
{
	for(int i=file.length()-1;i>=0;--i){
		if(file[i] == L'.'){
			return file.substr(i+1,file.length());
		}
	}
	return L"";
}
void MovieTraverser::backFolder()
{
	for(unsigned int i=this->curPath.length()-2;i>=0;--i){
		if(this->curPath[i] == L'\\'){
			this->curFolder = this->curPath.substr(i+1,this->curPath.length());
			this->curFolder.resize(this->curFolder.length()-1);
			this->curPath.resize(i+1);
			return;
		}
	}
}
/**STATIC FUNCTIONS**/
void MovieTraverser::init()
{
	if(MovieTraverser::initCount == 0){
		MovieTraverser::mOut->open(L"movies.xml",ios::out);
		MovieTraverser::mXMLWriter->setStream(MovieTraverser::mOut);
	}
	++MovieTraverser::initCount;
}
void MovieTraverser::deInit()
{
	--MovieTraverser::initCount;
	if(MovieTraverser::initCount <= 0){
		//delete this before mOut because XMLWriter use mOut
		delete MovieTraverser::mXMLWriter;
		MovieTraverser::mOut->close();
		delete MovieTraverser::mOut;
		delete MovieTraverser::mSem;
	}
}