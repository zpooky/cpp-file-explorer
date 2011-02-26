#include "movieTraverserThread.h"
#include <iostream>
#include <vector>
#include "spFunc.h"

using namespace std;

unsigned int movieTraverserThread::MAX_THREAD = 4;
unsigned int movieTraverserThread::CUR_THREADS = 0;

/**PUBLIC CONSTRUCTS**/

movieTraverserThread::movieTraverserThread()
{
	this->sem = new BinarySemaphore();
	this->TID = NULL;
	this->root = NULL;
	this->nrOf = 1;
	this->curPath = NULL;
	this->curFolder = NULL;
	this->prevFolder = NULL;
	this->isBack = NULL;
	this->start(1);
	wstring *arr = new wstring[1];
	arr[0] = L"C:\\";
	this->initiate(arr,1);
	delete[]arr;
}
movieTraverserThread::movieTraverserThread(const wstring &input)
{
	this->sem = new BinarySemaphore();
	this->TID = NULL;
	this->root = NULL;
	this->nrOf = 1;
	this->curPath = NULL;
	this->curFolder = NULL;
	this->prevFolder = NULL;
	this->isBack = NULL;
	this->start(1);
	wstring *arr = new wstring[1];
	arr[0] = input;
	this->initiate(arr,1);
	delete[]arr;
}
movieTraverserThread::movieTraverserThread(wstring *arr,int size)
{
	this->sem = new BinarySemaphore();
	this->TID = NULL;
	this->root = NULL;
	this->nrOf = size;
	this->curPath = NULL;
	this->curFolder = NULL;
	this->prevFolder = NULL;
	this->isBack = NULL;
	this->start(size);
	this->initiate(arr,size);
}

movieTraverserThread::~movieTraverserThread()
{
	this->out->close();
	delete this->sem;

	if(this->TID != NULL){
		delete[]this->TID;
	}
	if(this->root != NULL){
		delete[]this->root;
	}
	if(this->curPath != NULL){
		delete[]this->curPath;
	}
	if(this->curFolder != NULL){
		delete[]this->curFolder;
	}
	if(this->prevFolder != NULL){
		delete[]this->prevFolder;
	}
	if(this->isBack != NULL){
		delete[]this->isBack;
	}
	delete this->out;
	delete this->fe;
}

/**PUBLIC STATIC FUNCTIONS**/
void movieTraverserThread::setMaxThread(int threads)
{
	movieTraverserThread::MAX_THREAD = threads;
}
/**PUBLIC FUNCTIONS**/
void movieTraverserThread::setRoot(const wstring &root)
{
	/*this->root = root;
	this->curPath = this->root;*/
}
void movieTraverserThread::traverse()
{//fix that it will work with max threads
	for(int i=0;i<this->nrOf;++i){
		if(movieTraverserThread::CUR_THREADS < movieTraverserThread::MAX_THREAD){
			cout<<"thread"<<endl;
			parameter *param = new parameter();
		
			param->mtt = this;
			param->id = i;
			param->is_thread = true;
			//test and set
			++movieTraverserThread::CUR_THREADS;
			_beginthreadex(NULL,0,ThreadFunc,(void*)param,0,&this->TID[param->id]);
		} else {
			this->traverse(i);
		}
	}
}
/**PRIVATE FUNCTIONS**/
void movieTraverserThread::start(int length)
{
	if(this->TID != NULL){
		delete[]this->TID;
	}
	this->TID = new unsigned int[length];
	for(int i=0;i<length;++i){
		this->TID[i] = 0;
	}
	if(this->root != NULL){
		delete[]this->root;
	}
	this->root = new wstring[length];
	if(this->curPath != NULL){
		delete[]this->curPath;
	}
	this->curPath = new wstring[length];
	if(this->curFolder != NULL){
		delete[]this->curFolder;
	}
	this->curFolder = new wstring[length];
	if(this->prevFolder != NULL){
		delete[]this->prevFolder;
	}
	this->prevFolder = new wstring[length];
	if(this->isBack != NULL){
		delete[]this->isBack;
	}
	this->isBack = new bool[length];
	for(int i=0;i<length;++i){
		this->isBack[i] = false;
	}
}
void movieTraverserThread::initiate(wstring* root,int length)
{
	for(int i=0;i<length;++i){
		wstring tmp(root[i][root[i].length()-1] != '\\' ? root[i]+L'\\' : root[i]);
		this->root[i] = tmp;
		this->curPath[i] = this->root[i];
		this->isBack[i] = false;
	}
	this->out = new wofstream();
	this->out->open("movies.txt",ios::out);
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
bool movieTraverserThread::visit(const wstring &file,int id)
{
	wcout<<file<<endl;
	if(this->checkExt(file)){
		wcout<<file<<endl;
		this->write(file,id);
	}
	return true;
}
void movieTraverserThread::write(const wstring &input,int id)
{//semafore
		cout<<id<<"|";
		wcout<<input<<endl;
	//this->sem->signal(this->TID[id]);
	*this->out<<input+L"|"+this->curPath[id]+input<<endl;
	//this->sem->wait();
}
bool movieTraverserThread::checkExt(const wstring &file)
{
	wstring ext = this->getExt(file);
	/*if(file.substr((file.length()-ext.length()),file.length()-1) == ext){
	} else {
		wcout<<file<<endl;
	}*/
	//wcout<<ext<<endl;
	for(unsigned int i=0;i<movieExt.size();++i){
		//wcout<<movieExt.at(i)<<endl;
		if(movieExt.at(i).compare(ext) == 0){
			return true;
		}
	}
	return false;
}
wstring movieTraverserThread::getExt(const wstring &file)
{
	for(int i=(unsigned int)file.length()-1;i>=0;--i){
		if(file[i] == '.'){
			return file.substr(i+1,file.length());
		}
	}
	return L"";
}
void movieTraverserThread::backFolder(int id)
{
	for(unsigned int i=this->curPath[id].length()-2;i>=0;--i){
		if(this->curPath[id][i] == '\\'){
			this->curFolder[id] = this->curPath[id].substr(i+1,this->curPath[id].length());
			this->curFolder[id].resize(this->curFolder[id].length()-1);
			this->curPath[id].resize(i+1);
			return;
		}
	}
}
unsigned int WINAPI movieTraverserThread::ThreadFunc(void *p)
{
	parameter *param = (parameter*)p;
	movieTraverserThread *mtt = param->mtt;
	mtt->traverse(param->id);
	if(param->is_thread){
		//test and set
		--movieTraverserThread::CUR_THREADS;
	}
	delete param;
	return 0;
}
void movieTraverserThread::traverse(int id)
{
	cout<<id<<endl;
	vector<wstring> folder;
	this->curPath[id] = this->root[id];
	bool cont = true;
	FolderExplorer *fe = new FolderExplorer();
	//wcout<<this->curPath[id]<<endl;
	do{
		//wcout<<"_______"<<this->curPath<<endl;
		//system("pause");
		folder.clear();
		if(fe->open(this->curPath[id])){
			for(unsigned int i=0;i<fe->files.size();++i){
				//wcout<<this->fe->files.at(i).FileName<<" |"<<this->fe->files.at(i).isFolder<<"|"<<this->fe->files.at(i).dwFileAttributes<<endl;
				if(fe->files[i].dwFileAttributes == 18 || fe->files[i].dwFileAttributes == 22 || fe->files[i].dwFileAttributes == 48){

				} else
				if(fe->files[i].isFolder){
					folder.push_back(fe->files.at(i).FileName);
				} else 
				if(!this->isBack[id]){
					this->visit(fe->files.at(i).FileName,id);
				}
			}
			this->prevFolder[id] = this->curPath[id];
			if(this->isBack[id]){
				bool verify = true;
				for(unsigned int i=0;i<folder.size() && verify;++i){
					//cout<<"|"<<this->curFolder<<"| |"<<folder[i]<<"|"<<endl;
					if(this->curFolder[id] == folder[i]){
						++i;
						if(i<folder.size()){
							this->isBack[id] = false;
							this->curPath[id] += folder[i]+L"\\";
							this->curFolder[id] = folder[i];
						} else {
							this->isBack[id] = true;
							if(this->curPath[id] == this->root[id]){
								cont = false;
							} else {
								this->backFolder(id);
							}
						}
						verify = false;
					}
				}
			} else
			if(!this->isBack[id]){
				unsigned int i = 0;
				if(i<folder.size()){
					this->isBack[id] = false;
					this->curPath[id] += folder[i]+L"\\";
					this->curFolder[id] = folder[i];
				} else {
					this->isBack[id] = true;
					if(this->curPath[id] == this->root[id]){
						cont = false;
					} else {
						this->backFolder(id);
					}
				}
			}
		} else {
			cont = false;
		}
	}while(cont);
	delete fe;
}
bool movieTraverserThread::compare(const wstring &str1,const wstring &str2)
{
	if(str1.length() != str2.length()){
		return false;
	}
	for(unsigned int i=0;i<str1.length();++i){
		if(str1[i] != str2[i]){
			return false;
		}
	}
	return true;
}