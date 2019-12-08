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
void push(HTree *&root, char c, int freq);
int findchar(vector<char> input, char c);
void depose(HTree *root);
void pop(int i, vector<HTree*> &in);
HTree* add(HTree *p1, HTree *p2);
HTree* copy(HTree *p2);
void find2SmallFreq(vector<HTree*> &in, HTree *&p1, HTree *&p2);
HTree* creatHuffmanTree(vector<HTree*> &in);