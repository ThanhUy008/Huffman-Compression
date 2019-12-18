#pragma once
#include "Huffman.h"
#define MAX_BUFFER 1024*1024*4
struct Dictionary
{
	char _c;
	int _charfreq;
	string _binary;
};
//set the char with a suitable binary value from huffman tree
void initDistionary(HTree* huffman, Dictionary &temp, vector<Dictionary> &output);

struct FreqTable
{
	vector<int> _freq;
	vector<char> _char;
};
//get the freq of all char in file input
vector<HTree*> handleInputFile(char *file, FreqTable &table);

//create a string to save huffman tree after compress
void creatsaveTree(HTree *in, string &temp);

struct TXTHEADER
{
	char _type[3];
	string _filename;
	string _duoifile;
	string _treesize;
	char *_tree;

	string _numberofcharaftercompress;
	string _realtextsize;
	string _textsize;
};

struct FILESAVE
{
	bool isFoler;

	string name;
};

struct FOLDERHEADER
{
	char _type[3];
	string _foldername;
	string _numberoffile;
};

//create the header file
void createtxtHeader(TXTHEADER &header, string tree, vector<Dictionary> dic,string duoifile);
//set the postion of char in dictionary to freqtable
void sortDic(vector<Dictionary> &dictionary, FreqTable &table);

void disposetable(TXTHEADER &header);