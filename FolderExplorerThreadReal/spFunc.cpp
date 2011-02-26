#include "spFunc.h"
#include <iostream>
#include <ctime>
#include <cctype>
//#include <boost/regex.hpp>

using namespace std;

void sp_explode(string split,string var,int &index,int size,string chunks[],int limit)//working
{
	int i,
		a = 0;
	if(split != ""){
		bool verify = false;
		string chunk;
		index = 0;
		for(i=0;i<(int)var.length();++i){
			if(var[i] == split[a]){
				++a;
				if(a == (int)split.length()){
					verify = true;
				}
			} else {
				a = 0;
				chunk += var[i];
			}
			if(verify){
				a = 0;
				verify = false;
				chunks[index++] = chunk;
				chunk = "";
				if(index == size)
					i = (int)var.length();
				if(index == limit){
					chunks[index++] = var.substr(i+1,var.length());
					i = (int)var.length();
				}
			}
		}
		if(index != size && limit <= 0)
			chunks[index++] = chunk;
	} else {
		for(i=0;i<(int)var.length();++i){
			chunks[a] += var[i];
			if(i < size-1){
				++a;
			}
		}
		index = a;
		if(a!=i)
			++index;
	}
}

string sp_implode(string divider,string chunks[],int index)//working
{
	int i;
	string var = "";
	var = chunks[0];
	for(i=1;i<index;++i){
		var += divider+chunks[i];
	}
	return var;
}/*
string sp_date(string input)
{
	int i;
	string dayOfWeekShort[7] = {"Mon","Thu","Wen","Thu","Fri","Sat","Sun"};
	string dayOfWeekLong[7] = {"Monday","Thursday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	string monthShort[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	string monthLong[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	int daysOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	time_t msec;
	string date;
	string tmp;
	char character;
	for(i=0;i<(int)input.length();++i){
		msec = time(NULL);
		character = (char)input[i];
		switch(character){
		case 'd':
		break;
		case 'D':
		break;
		case 'j':
		break;
		case 'l':
		break;
		case 'N':
		break;
		case 'S':
		break;
		case 'w':
		break;
		case 'z':
		break;
		case 'W':
		break;
		case 'F':
		break;
		case 'm':
		break;
		case 'M':
		break;
		case 'n':
		break;
		case 't':
		break;
		case 'L':
		break;
		case 'o':
		break;
		case 'Y':
		break;
		case 'y':
		break;
		case 'a':
		break;
		case 'A':
		break;
		case 'B':
		break;
		case 'g'://not working test later when working
			msec /= 60;
			msec /= 60;
			tmp = sp_toString((int)msec%24);
			date += (int)msec%12 > 9 ? "" : "0";
			date += tmp;
		break;
		case 'G':
			msec /= 60;
			msec /= 60;
			date += sp_toString((int)msec%24);
		break;
		case 'h'://not working test later when working
			msec /= 60;
			msec /= 60;
			date = sp_toString((int)msec%12);
		break;
		case 'H':
			msec /= 60;
			msec /= 60;
			tmp = sp_toString((int)msec%24);
			date += (int)msec%24 > 9 ? "" : "0";
			date += tmp;
		break;
		case 'i'://working??
			msec /= 60;
			tmp = sp_toString((int)msec%60);
			date += (int)msec%60 > 9 ? "" : "0";
			date += tmp;
		break;
		case 's':
			tmp = sp_toString((int)msec%60);
			date += (int)msec%60 > 9 ? "" : "0";
			date += tmp;
		break;
		case 'u':
		break;
		case 'e':
		break;
		case 'I':
		break;
		case 'O':
		break;
		case 'P':
		break;
		case 'T':
		break;
		case 'Z':
		break;
		case 'c':
		break;
		case 'r':
		break;
		case 'U':
		break;
		default:
			date += input[i];
		}
	}
	return date;
}*/

string sp_replace(string replace,string value,string input)
{
	int index = 0,
		size = (int)input.length()/(int)value.length();
	string *chunks = new string[size];
	sp_explode(replace,input,index,size,chunks);
	input = sp_implode(value,chunks,index);
	delete[]chunks;
	return input;
}

int sp_rand(int start,int end)//working
{
	return rand()%(end-(start-1))+start;
}
int sp_toInt(string nr)//working
{
	int temp;
	temp=atoi(nr.data());
	return temp;
}
double sp_toDouble(string nr)//working
{
	double temp;
	temp=atof(nr.data());
	return temp;
}
string sp_toString(int nr)//working
{
	char *temp=new char[10];
	_itoa_s(nr, temp, 10, 10);
	return temp;
}
string sp_toString(double nr)//working
{
	char *temp=new char[20];
	sprintf_s(temp, 20, "%.19g", nr );     
	return temp;
}

string sp_shuffle(string input)//working
{
	string value = input;
	int i,
		key,
		max = (int)value.length();
	for(i=0;i<max;++i){
		key = sp_rand(0,max-1);
		sp_swap(value[i],value[key]);
	}
	return value;
}

/*
string sp_pad(string input,int length,string add,const char flag)
{
	
}
*/

string sp_repeat(string repeat,int times)//working
{
	int i;
	string value = "";
	for(i=0;i<times;++i)
		value += repeat;
	return value;
}

void sp_split(string input,int length,int &index,int size,string chunks[])//working
{
	index = 0;
	int i,
		a = 0;
	for(i=0;i<(int)input.length();++i){
		++a;
		chunks[index] += input[i];
		if(a==length){
			a = 0;
			++index;
			if(index == size)//change to add values into the last chunk instead of quiting loop??
				i = (int)input.length();
		}
	}
	if((int)chunks[index].length() < length && (int)chunks[index].length() > 0)
		++index;
}

string sp_randomize(string pool,int length)//working
{
	int i,
		pLength = (int)pool.length()-1;
	string value = "";
	for(i=0;i<length;++i){
		value += pool[sp_rand(0,pLength)];
	}
	return value;
}

int sp_count_char(string search,string input)//working
{
	int i,
		a = 0,
		count = 0,
		sLength = (int)search.length();
	for(i=0;i<(int)input.length();++i){
		if(input[i] == search[a]){
			++a;
			if(a==sLength){
				a = 0;
				++count;
			}
		} else {
			a = 0;
		}
	}
	return count;
}
/*
bool sp_is_lowercase(string input)//working
{
	int i;
	bool verify = true;
	for(i=0;i<(int)input.length()&&verify;++i){
		if(sp_is_letter((char)input[i])){
			if(input[i] < 'a' || input[i] > 'z'){
				verify = false;
			}
		}
	}
	return verify;
}*/

bool sp_is_uppercase(string input)//working
{
	int i;
	bool verify = true;
	for(i=0;i<(int)input.length()&&verify;++i){
		if(sp_is_letter((char)input[i])){
			if(input[i] < 'A' || input[i] > 'Z'){
				verify = false;
			}
		}
	}
	return verify;
}

bool sp_is_numeric(string input)//working
{
	int i;
	bool verify = true;
	for(i=0;i<(int)input.length()&&verify;++i){
		if(sp_is_letter((char)input[i])){
			if((char)input[i] >= 48 || (char)input[i] <= 57){
				verify = false;
			}
		}
	}
	return verify;
}

bool sp_is_letter(char input)//working
{
	if(input >= 'A' && input <= 'Z' || (input >= 'a' && input <= 'z'))
		return true;
	else
		return false;
}
/*
bool sp_is_alphanumeric(string input)
{
	int i;
	bool verify = true;
	for(i=0;i<(int)input.length()&&verify;++i){
		if(!sp_is_letter((char)input[i])){
			if(input[i] < 'A' || input[i] > 'Z'){
				verify = false;
			}
		}
	}
	return verify;
}*/

int sp_array_bend(int pos,int steps, int size)//working
{
	int bend = pos+1+steps,
		returnPos;
	if(bend == size){
		returnPos = size-1;
	}else
	if(bend > size){
		returnPos = (bend%size)-1;
	} else {
		returnPos = bend-1;
	}
	return returnPos;
}
/*
string sp_rot13(string input)//working
{
	string lowercase[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
	string uppercase[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	string value = "";
	string tmp;
	int i,
		pos,
		newPos;
	for(i=0;i<(int)input.size();++i){
		tmp = input[i];
		if(sp_is_uppercase(tmp)){
			pos = sp_linear_search(tmp,uppercase,26);
			newPos = sp_array_bend(pos,13,26);
			value += uppercase[newPos];
		} else 
		if(sp_is_lowercase(tmp)){
			pos = sp_linear_search(tmp,lowercase,26);
			newPos = sp_array_bend(pos,13,26);
			value += lowercase[newPos];
		} else {
			value += tmp;
		}
	}
	return value;
}*/

string sp_uppercase(string input)
{
	int i;
	for(i=0;i<(int)input.size();++i){
		input[i] = toupper(input[i]);
	}
	return input;
}

string sp_lowercase(string input)
{
	int i;
	for(i=0;i<(int)input.size();++i){
		input[i] = tolower(input[i]);
	}
	return input;
}
string sp_reverse(string input,int n)
{
	if(n == -1)
		n = input.size();
	string tmp;
	if(n == 1){
		tmp = input[0];
		return tmp;
	} else {
		return input[n-1]+sp_reverse(input,n-1);
	}
}

string sp_substr_replace(int start,int end,string replace,string input)//recheck
{
	int i;
	string output;
	for(i=0;i<start;++i){
		output += input[i];
	}
	output += replace;
	for(i=end;i<(int)input.size();++i){
		output += input[i];
	}
	return output;
}

string sp_substr(int start,int end,string input)//working
{
	if(end > (int)input.size()-1)
		end = (int)input.size()-1;
	if(start < 0)
		start = 0;
	int i;
	string output;
	for(i=start;i<=end;++i){
		output += input[i];
	}
	return output;
}

bool sp_substr_compare(int start,int end,string search,string input)//working
{
	if(sp_substr(start,end,input) == search)
		return true;
	else
		return false;
}
/*
bool sp_compare(string var1,string var2,int caseSencetive)
{//cant check before fixing the template bug
	int i,
		pos;
	bool verify = false;
	string tmp;
	char lowercase[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char uppercase[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	if(var1 == var2)//check with case sencetive
		return true;
	if(caseSencetive == 1)//if case sencetive then stop
		return false;
	if(var1.length() != var2.length())
		return false;
	
	for(i=0;i<(int)var1.length();++i){
		tmp = var1[i];
		if(sp_is_lowercase(tmp)){
			pos = sp_binary_search(tmp,lowercase,26);
		} else
		if(sp_is_uppercase(tmp)){
			pos = sp_binary_search(tmp,uppercase,26);
		} else
		if(var1[i] != var2[i]){
			return false;
		}
		if(var2.c_str()[i] != lowercase[pos] && var2.c_str()[i] != uppercase[pos]){
			return false;
		}
	}
	return verify;
}
*/
string sp_strstr(string needle,string input)
{
	bool verify = false;
	string output = "";
	int i,
		a = 0;
	for(i=0;i<(int)input.length();++i){
		if(needle[a] == input[i] && !verify){
			++a;
			if(a == (int)needle.length()){
				verify = true;
			}
		} else {
			a = 0;
		}
		if(verify){
			if(a == (int)needle.length()){
				output = needle;
			} else {
				output += input[i];
			}
		}
	}
	return output;
}
void sp_chunk(char separater,char stop,string input,string output[],int &index,int size)
{
		bool verify = true;
		string chunk;
		index = 0;
		for(int i=0;i<(int)input.length();++i){
			if(input[i] == stop)
				verify = verify ? false : true;
			if(verify && input[i] == separater){
				output[index++] = chunk;
				chunk = "";
				if(index == size-1){
					output[index++] = input.substr(i+1,input.length());
					i = (int)input.length();
				}
			} else {
				if(input[i] != stop)
					chunk += input[i];
			}
		}
}
unsigned int sp_calc_bin(const string &input)
{
	unsigned int output = 0;
	unsigned int value = 1;
	for(int i=input.length()-1;i>=0;--i){
		if(input[i] == '1'){
			output += value;
		}
		value *= 2;
	}
	return output;
}
void sp_natural_sort(string input[],int size)
{
	int i,
		lowest,
		k;
	for(i=0;i<(size-1);++i){
		lowest = i;
		for(k=i+1;k<size;++k){
			if(input[lowest]>input[k]){
				lowest = k;
			}
		}
		sp_swap(input[lowest],input[i]);
	}
}