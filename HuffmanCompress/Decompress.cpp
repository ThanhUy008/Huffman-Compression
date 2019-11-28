#include "Decompress.h"

string readTXTheader(char* infile)
{
	ifstream inFILE;
	//open by txt

	//string infilename(infile);
	//for (int i = 0; i < 5; i++)
	//	infilename.pop_back();
	//infilename += ".txt";

	inFILE.open(infile);
	if (inFILE.fail())
	{
		cout << "CANT OPEN UZIP FILE";
		exit(0);
	}
	//lay chu signature txt
	string rash;
	for (int i = 0; i < 3; i++)
	{
		char trash;
		inFILE >> noskipws >> trash;
		rash.push_back(trash);
	}
	//doc table size fail
	unsigned int Treesize = 0;
	inFILE  >> Treesize;
	string saveTree = "";
	for (int i = 0; i < Treesize; i++)
	{
		unsigned char c_char;
		inFILE >> noskipws >> c_char;
		saveTree += c_char;
	}
	return saveTree;
}
void pop_first(string &s)
{
	for (int i = 0; i < s.size() - 1; i++)
	{
		s[i] = s[i + 1];
	}
	s.pop_back();
}

void rebuildHuffman(string &b, HTree *&root)
{
	if (root == NULL)
	{
		if (!b.empty())
		{
			if (b[0] == '0')
			{
				root = new HTree;
				//create root node
				root->_char = '#';
				root->_freq = 0;
				root->pLeft = NULL;
				root->pRight = NULL;
				//remove '0' in the string
				pop_first(b);

				rebuildHuffman(b, root->pLeft);

				rebuildHuffman(b, root->pRight);
			}
			else if (b[0] == '1')
			{
				//create leaf node
				root = new HTree;
				root->pLeft = NULL;
				root->pRight = NULL;
				root->_char = b[1];
				root->_freq = 0;
				//remove '1' in the string and a character right after it
				pop_first(b);
				pop_first(b);
				//jump to node right
			}
		}
	}
}
