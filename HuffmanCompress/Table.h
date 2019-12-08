#pragma once
#include "Huffman.h"
#define MAX_BUFFER 1024*1024*4
struct Dictionary
{
	char _c;
	string _binary;
};

void initDistionary(HTree* huffman, Dictionary &temp, vector<Dictionary> &output);

struct FreqTable
{
	vector<int> _freq;
	vector<char> _char;
};

vector<HTree*> handleInputFile(char *file, FreqTable &table);
void creatsaveTree(HTree *in, string &temp);

struct TXTHEADER
{
	char _type[3];
	string _treesize;
	char *_tree;

	string _realtextsize;
//	string _textsize;
};
void createtxtHeader(TXTHEADER &header, string tree, FreqTable table,string duoifile);
void sortDic(vector<Dictionary> &dictionary, FreqTable &table);
void disposetable(TXTHEADER &header);