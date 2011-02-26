#ifndef SPFUNC_H
#define SPFUNC_H
#include <string>
#include <windows.h>
using namespace std;

/*
@author Fredrik Olsson
@desc swaps the value of 2 variables
@param  T &var1,T &var2
@return void*/
template <class T>
void sp_swap(T &var1,T &var2)//working
{
	T tmp = var1;
	var1 = var2;
	var2 = tmp;
}
/*
@author Fredrik Olsson
@desc splits a given string into array. divider by split can limit nr ocf chunks
@param string split: where the string will be split,string var: input,int &index: nr of items in array,int size: size of array,string chunks[]: return array,int limit is max nr of chunks default endless
@return void*/
void sp_explode(string split,string var,int &index,int size,string chunks[],int limit = 0);
/*
@author Fredrik Olsson
@desc convert array into string element divided by given divider
@param string divider: what the elements will be divided,string chunks[]: array that will be converted,int size: size of array
@return converted string*/
string sp_implode(string divider,string chunks[],int index);
/*
@author Fredrik Olsson
@desc convert given keyword into date
@param string input: string with keywords
@return string with date*/
string sp_date(string input);
/*
@author Fredrik Olsson
@desc replace chars with other chars
@param string replace: what will be replaced,string value: what will be replaced to,string input: what will be changed
@return changed string*/
string sp_replace(string replace,string value,string input);
/*
@author Fredrik Olsson
@desc return a random number between give param
@param int start: min value,int end: max value
@return random number*/
int sp_rand(int start,int end);
/*
@author Fredrik Olsson
@desc converts string into int
@param string nr: string that will be converted
@return converted int*/
int sp_toInt(string nr);
/*
@author Fredrik Olsson
@desc converts string into double
@param string nr: string that will be converted
@return converted double*/
double sp_toDouble(string nr);
/*
@author Fredrik Olsson
@desc converts int into string
@param int nr: int that will be converted
@return converted string*/
string sp_toString(int nr);
/*
@author Fredrik Olsson
@desc converts double into string
@param double nr: double that will be converted
@return converted string*/
string sp_toString(double nr);
/*
@author Fredrik Olsson
@desc shuffle string
@param string input: unshuffled string 
@return shuffled string*/
string sp_shuffle(string input);
string sp_pad(string,int,string);
/*
@author Fredrik Olsson
@desc split string int array elements
@param string repeat: repeat,int times: repeat nr of time
@return repeatet string*/
string sp_repeat(string repeat,int times);
/*
@author Fredrik Olsson
@desc split string int array elements
@param string input: input,int length: chunk length,int &index: size of return array,int size: array size,string chunks[]: return array
@return void*/
void sp_split(string input,int length,int &index,int size,string chunks[]);
/*
@author Fredrik Olsson
@desc generate a random string
@param string pool: aviable char the string will consist of,int length: the length of the string
@return random string*/
string sp_randomize(string pool,int length);
/*
@author Fredrik Olsson
@desc count the nr of occurence
@param string search: occurence to be countet,string input: counted from
@return nr of occurence*/
int sp_count_char(string search,string input);
/*
@author Fredrik Olsson
@desc checks if string is just lowercase
@param string input: search string
@return true/false*/
bool sp_is_lowercase(string input);
/*
@author Fredrik Olsson
@desc checks if string is just uppercase
@param string input: search string
@return true/false*/
bool sp_is_uppercase(string input);
/*
@author Fredrik Olsson
@desc checks if string is just numeric(not working with . ,)
@param string input: search string
@return true/false*/
bool sp_is_numeric(string input);
/*
@author Fredrik Olsson
@desc checks if char is a letter
@param char input: search char
@return true/false*/
bool sp_is_letter(char input);

bool sp_is_alphanumeric(string input);
/*
@author Fredrik Olsson
@desc determen new position if when out of bounds start in begining
@param int pos: start position,int steps: nr of steps, int size: size of array
@return position of new element in array*/
int sp_array_bend(int pos,int steps, int size);
/*
@author Fredrik Olsson
@desc shifts every letter by 13 places in the alphabet
@param string input: unencoded string
@return encoded string*/
string sp_rot13(string input);
/*
@author Fredrik Olsson
@desc converts all lowercase characters to uppercase
@param string input: input string
@return uppercase string*/
string sp_uppercase(string input);
/*
@author Fredrik Olsson
@desc converts all uppercase characters to lowercase
@param string input: input string
@return lowercase string*/
string sp_lowercase(string input);
/*
@author Fredrik Olsson
@desc reverse string
@param string input: input string, int n: size of string(optional)
@return reverse string*/
string sp_reverse(string input,int n = -1);
/*
@author Fredrik Olsson
@desc replace at given cordinats
@param int start: between not counting start,int end: between not counting end,string replace: what to replace,string input: where to replace
@return replaced string*/
string sp_substr_replace(int start,int end,string replace,string input);
/*
@author Fredrik Olsson
@desc return chunk from given cordinants
@param int start: from (including),int end: stop(including),string input: input string
@return string chunk*/
string sp_substr(int start,int end,string input);
/*
@author Fredrik Olsson
@desc compare chunk to compare
@param int start: start pos,int end: stop pos,string search: search,string input: search string
@return true/false*/
bool sp_substr_compare(int start,int end,string search,string input);
/*
@author Fredrik Olsson
@desc compare two strings case/not case sensetivity
@param string var1: compare string 1,string var2: compare string 2,int caseSencetive = 0: 1:yes 0:no
@return true/false*/
bool sp_compare(string var1,string var2,int caseSencetive = 0);
/*
@author Fredrik Olsson
@desc Returns part of haystack string from the first occurrence of needle to the end of input
@param string needle: occurence,string input: search
@return part of input*/
string sp_strstr(string needle,string input);
/*
@author Fredrik Olsson
@desc (test function that perhaps will not be usefull for more than filetransport program) chunk a string stop chunking when stop var is found and return chunking when stop is found againg
@param char separater: where string will be chunked, char stop: when stop/start chunking, string input: var that will be searched,string output[]: output chunks,int nrOfChunks: nr of chunks int output[],int size: size of output[]
@return void*/
void sp_chunk(char separater,char stop,string input,string output[],int &index,int size);
/*
@author Fredrik Olsson
@desc calculates binary to numeric
@param const string &input: binary string
@return unsigned int: value*/
unsigned int sp_calc_bin(const string &input);

string sp_stristr(string needle,string input);

int sp_strpos(string search,string input);//search in string || add return in array
/*
@author Fredrik Olsson
@desc shuffle elements in array
@param T input[]: in array,int size: elements in array
@return void*/
template <class T>
void sp_array_shuffle(T input[],int size)
{
	int i,
		pos;
	for(i=0;i<size;++i){
		pos = sp_rand(0,size-1);
		sp_swap(input[i],input[pos]);
	}
}
/*
@author Fredrik Olsson
@desc removes all duplicate values in array
@param T input[]: in array,int &size: elements in array and new nr of elements
@return void*/
template <class T>
void sp_array_unique(T input[],int &size)
{
	int i,
		a,
		b = 0,
		pos[20];
	for(i=0;i<size;++i){
		for(a=i+1;a<size;++a){
			if(input[i] == input[a]){
				pos[b++] = a;
			}
		}
	}
	for(i=0;i<b;++i){
		sp_array_remove(pos[i],input,size,1);
	}
}
/*
@author Fredrik Olsson
@desc remove pos value from array either moving the last value to removed pos or move all steps upp one step
@param int pos: pos of value that will be removed,T input[]: input array,int &size: elements in array,int flag: 1: keep order 0:last to pos
@return void*/
template <class T>
void sp_array_remove(int pos,T input[],int &size,int flag = 0)
{
	if(flag == 0){
		input[pos] = input[size-1];
	} else {
		for(int i=pos;i<size-1;++i){
			input[i] = input[i+1];
		}
	}
	--size;
}
/*
@author Fredrik Olsson
@desc fill array with give value
@param T value: fill value,T insert[]: in array,int size: size of array
@return void*/
template <class T>
void sp_array_fill(T value,T insert[],int size)//fungerar inte?
{
	for(int i=0;i<size;++i){
		insert[i] = value;
	}
}
/*
@author Fredrik Olsson
@desc return a array with values that is in array 1 but not in array2
@param T input1[]: first array,int size1: size of first array,T input2[]: compare array,int size2: size of compare array,T output[]: output array,int size: size of output array,int &index: nr of elements in array
@return void*/
template <class T>
void sp_array_diff(T input1[],int size1,T input2[],int size2,T output[],int size,int &index)
{
	int i,
		a,
		b = 0;
	bool verify;
	for(i=0;i<size1;++i){
		verify = true;
		for(a=0;a<size2;++a){
			if(input1[i] == input2[a]){
				verify = false;
				a = size2;
			}
		}
		if(verify){
			output[b++] = input1[i];
			if(size == b){
				i = size1;
			}
		}
	}
	sp_array_unique(output,b);
	index = b;
}
/*
@author Fredrik Olsson
@desc prints ellements in array
@param T input[]: input array,int size: size of array
@return void*/
template <class T>
void sp_print_r(T input[],int size)
{
	int i;
	cout<<"Array(";
	for(i=0;i<size;++i){
		cout<<"["<<i<<"] => \""<<input[i]<<"\" ";
	}
	cout<<")"<<endl;
}
/*
@author Fredrik Olsson
@desc prints ellements in array
@param T input[]: input array,int size1: size of array,T output[]: output reversed array
@return void*/
template <class T>
void sp_array_reverse(T input[],int size1,T output[])
{
	int i,
		a = 0;
	for(i=size1-1;i>=0;--i){
		output[a++] = input[i];
	}
}
//SORT FUNCTIONS
void sp_natural_sort(string input[],int size);
template <class T>
void sp_selection_sort(T input[],int size)//unknown link error
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
template <class T>
void sp_bubble_sort(T input[],int size)
{
	bool verify;
	int i;
	do{
		verify = false;
		for(i=0;i<size-1;++i){
			if(input[i] > input[i+1]){
				sp_swap(input[i],input[i+1]);
				verify = true;
			}
		}
	}while(verify);
}
template <class T>
int sp_partition(T input[],int start,int end)//unknown link error
{
	int pivot = start,
		i;
	for(i=start+1;i<=end;++i){
		if(input[i] < input[pivot]){
			sp_swap(input[pivot+1],input[i]);
			sp_swap(input[pivot],input[pivot+1]);
			++pivot;
		}
	}
	return pivot;
}
template <class T>
void sp_quick_sort(T input[],int end,int start = 0)//unknown link error
{
	static bool verify = true;
	if(verify){
		--end;
		verify = false;
	}
	if(start<end){
		int pivot = sp_partition(input,start,end);
		sp_quick_sort(input,pivot-1,start);
		sp_quick_sort(input,end,pivot+1);
	}
}

//SEARCH FUNCTIONS

/*
@author Fredrik Olsson
@desc Returns the numeric position of the first occurrence of needle  in the haystack
@param T search: what to search for, T input[]: what to search in,int size: size of array
@return position of the first find in array*/
template <class T>
int sp_linear_search(T search, T input[],int size)
{
	int pos = -1,
		i;
	for(i=0;i<size;++i){
		if(search == input[i]){
			pos = i;
			i = size;
		}
	}
	return pos;
}
/*
@author Fredrik Olsson
@desc search array
@param T search: what to search for, T input[]: what to search in,int size:size of input array,int &index: nr of elements in outpur, int oSize: output array size, T output[]: output array
@return true/false if something found*/
template <class T>
bool sp_linear_search_all(T search, T input[],int size,int &index, int oSize, T output[])
{
		int i;
		index = 0;
		bool verify = false;
	for(i=0;i<size;++i){
		if(search == input[i]){
			if(index == size){
				i = size;
			}
			verify = true;
			output[index] = i;
		}
	}
	return verify;
}
template <class T>
int sp_binary_search(T search, T input[],int size)
{
	sp_quick_sort(input,size);
	int pos = -1,
		first = 0,
		last = size-1,
		middle;
	bool verify = false;
	while(!verify  && first <= last){
		middle = (first+last)/2;
		if(search == input[middle]){
			pos = middle;
			verify = true;
		} else
		if(search < input[middle]){
			last = middle-1;
		} else
		if(search > input[middle]){
			first = middle+1;
		}
	}
	return pos;
}
/*
template <class T>
void sp_expand(int expand,T *input[],int nrOfElements)//??
{
	int i;
	T tmp = new T[nrOfElements+expand];
	for(i=0;i<nrOfElements;++i){
		tmp[i] = input[i];
	}
	delete[]input;
	input = tmp;
}*/
//NUMERIC FUNCTIONS
template <class T>
T sp_medelvarde(T input[],int index)
{
	int i;
	T output = 0;
	for(i=0;i<index;++i){
		output += input[i];
	}
	return (T)output/index;
}
template <class T>
T sp_median(T input[],int index)
{
	if(index%2==0){
		return ((input[index/2]+input[(index/2)+1])/2);
	} else {
		return input[(index/2)+1];
	}
}
template <class T>
T sp_array_product(T input[],int size)
{
	int i;
	T output = 0;
	for(i=0;i<size;++i){
		output += input[i];
	}
	return output;
}
#endif