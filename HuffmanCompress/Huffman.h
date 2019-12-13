#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
using namespace std;

struct HTree
{
	int _freq;
	char _char;
	HTree *pLeft, *pRight;
};


void initTree(HTree *&root);
//create a leaf node withou parent
void push(HTree *&root, char c, int freq);
//find the character postion
int findchar(vector<char> input, char c);


void depose(HTree *root);
//remove the i-th value from vector<leafnode>
void pop(int i, vector<HTree*> &in);
//add two node together
HTree* add(HTree *p1, HTree *p2);
//copy a node
HTree* copy(HTree *p2);
//find the smallest freq node
void find2SmallFreq(vector<HTree*> &in, HTree *&p1, HTree *&p2);
//build huffman tree
HTree* creatHuffmanTree(vector<HTree*> &in);