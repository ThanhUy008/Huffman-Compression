#include "Huffman.h"



void initTree(HTree *&root)
{
	root = NULL;
}
void print(HTree *root)
{
	if (root != NULL)
	{
		print(root->pLeft);

		cout << root->_char << " freq is " << root->_freq << endl;

		print(root->pRight);

	}
}
void push(HTree *&root, char c, int freq)
{
	if (root == NULL)
	{
		root = new HTree;
		root->_char = c;
		root->_freq = freq;
		root->pLeft = NULL;
		root->pRight = NULL;
	}
}
int findchar(vector<char> input, char c)
{
	int rel = -1;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == c)
		{
			rel = i;
		}
	}
	return rel;
}
void depose(HTree *root)
{
	if (root != NULL)
	{
		depose(root->pLeft);
		depose(root->pRight);
		delete root;
	}
}
void pop(int i, vector<HTree*> &in)
{
	vector<HTree*>temp;
	HTree *p2;
	depose(in[i]);
	for (int k = i; k < in.size() - 1; k++)
	{
		in[k] = in[k + 1];
	}
	in.pop_back();
}
//p1 < p2
HTree* add(HTree *p1, HTree *p2)
{
	HTree *rel = new HTree;
	rel->_freq = p1->_freq + p2->_freq;
	rel->_char = NULL;
	rel->pLeft = p1;
	rel->pRight = p2;
	return rel;
}
HTree* copy(HTree *p2)
{
	if (p2 != NULL)
	{
		HTree *rel;
		rel = new HTree;
		rel->pLeft = NULL;
		rel->pRight = NULL;
		if (p2->pLeft != NULL)
		{
			rel->pLeft = copy(p2->pLeft);
		}

		if (p2->pRight != NULL)
		{
			rel->pRight = copy(p2->pRight);
		}
		rel->_char = p2->_char;
		rel->_freq = p2->_freq;
		return rel;
	}
	else
	{
		return NULL;
	}
}
void find2SmallFreq(vector<HTree*> &in, HTree *&p1, HTree *&p2)
{
	if (in.size() >= 2)
	{
		p1 = copy(in[0]);
		int temp = 0;
		for (int i = 0; i < in.size(); i++)
		{
			if (in[i]->_freq < p1->_freq)
			{
				p1 = copy(in[i]);
				temp = i;
			}
		}
		pop(temp, in);

		p2 = copy(in[0]);
		temp = 0;
		for (int i = 0; i < in.size(); i++)
		{
			if (in[i]->_freq < p2->_freq)
			{
				p2 = copy(in[i]);
				temp = i;
			}
		}
		pop(temp, in);
	}
	else
	{
		return;
	}
}
HTree* creatHuffmanTree(vector<HTree*> &in)
{
	HTree *p1, *p2;
	while (in.size() > 1)
	{
		find2SmallFreq(in, p1, p2);
		HTree *addresult;
		addresult = add(p1, p2);
		in.push_back(addresult);
	}
	if(!in.empty())
	return in[0];
	else return NULL;
}
