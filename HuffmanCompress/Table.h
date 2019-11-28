#pragma once
#include "Huffman.h"
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
	unsigned int _tabsize;
	unsigned char *_table;

	unsigned int _realtextsize;
	unsigned int _textsize;
};
void createtxtHeader(TXTHEADER &header, string tree, vector<Dictionary> diction, FreqTable table);
void disposetable(TXTHEADER &header);