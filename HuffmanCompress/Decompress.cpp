#include "Decompress.h"
#include <bitset>

void reconvert(string &b, char &c, HTree *root, int &i)
{
	if(b.empty())
	{
		c = '#';
		return;
	}
	if (i > b.size())
	{
		c = '#';
		return;
	}
	if (root->pLeft == NULL && root->pRight == NULL)
	{
		c = root->_char;
	}
	else
	{
		
		if (b[i] == '0')
		{
			i++;
			reconvert(b, c, root->pLeft, i);
		}
		else
		{
			i++;
			reconvert(b, c, root->pRight, i);
		}
	}
}
void Decompression(char* infile)
{
	ifstream inFILE;
	

	string outfilename(infile);
	for (int i = 0; i < 5; i++)
		outfilename.pop_back();
	outfilename += "1.txt";

	ofstream outFILE;
	outFILE.open(outfilename,ios::binary);

	inFILE.open(infile,ios::binary);
	if (inFILE.fail())
	{
		cout << "CANT OPEN UZIP FILE";
		exit(0);
	}
	//lay chu signature txt
	string rash;
	char trash;
	for (int i = 0; i < 3; i++)
	{
		inFILE >> noskipws >> trash;
		rash.push_back(trash);
	}

	TXTHEADER header;
	inFILE >> noskipws >> trash;

	while (inFILE.peek() != '/')
	{
		char temp;
		inFILE >> noskipws >> temp;
		header._tabsize.push_back(temp);
	}

	//dipose the last '/'
	inFILE >> noskipws >> trash;

	int Treesize = atoi(header._tabsize.c_str());
	
	string saveTree = "";
	for (int i = 0; i < Treesize; i++)
	{
		char c_char;
		inFILE.read(&c_char, 1);
		saveTree += c_char;
	}
	
	//dipose the last '/'
	inFILE >> noskipws >> trash;

	while (inFILE.peek() != '/')
	{
		char temp;
		inFILE >> noskipws >> temp;
		header._realtextsize.push_back(temp);
	}

	//dipose the last '/'
	inFILE >> noskipws >> trash;

	//while (inFILE.peek() != '/')
	//{
	//	char temp;
	//	inFILE >> noskipws >> temp;
	//	header._textsize.push_back(temp);
	//}
	////dipose the last '/'
	//inFILE >> noskipws >> trash;
	//

	int realtextsize = stoi(header._realtextsize);
//	int textsize = stoi(header._textsize);
	HTree* root = NULL;
	rebuildHuffman(saveTree, root);
	char temp;
	string buffer = "";
	int count = 0;
	while (inFILE >> noskipws >> temp)
	{
		
		buffer += bitset<8>(temp).to_string();
		
	//	if (count >= realtextsize) break;
		char c_buffer = ' ';
		while (c_buffer != '#')
		{
			if (count >= realtextsize) break;
			int index = 0;
			reconvert(buffer, c_buffer, root, index);
			if (c_buffer != '#')
			{
				pop_first_n(buffer, index);
				outFILE.write(&c_buffer, 1);
				count++;
			}
		}
	}
	//int need_pop = textsize - realtextsize;
	////TODO : FIX THIS
	//while (need_pop > 0)
	//{
	//	if(!buffer.empty())
	//	buffer.pop_back();
	//	need_pop--;
	//}

	//char c_buffer;
	//int index = 0;
	//reconvert(buffer, c_buffer, root, index);
	//if (c_buffer != '#')
	//{
	//	outFILE.write(&c_buffer, 1);
	//}
	//outFILE.write(&c_buffer, 1);
	inFILE.close();
	outFILE.close();
}
void pop_first_8(string &b)
{
	string temp = "";
	for (int i = b.size() - 1; i >= 8; i--)
	{
		temp += b[i];
	}
	b = temp;
}
void pop_first(string &s)
{
	for (int i = 0; i < s.size() - 1; i++)
	{
		s[i] = s[i + 1];
	}
	s.pop_back();
}
void pop_first_n(string &b, int index)
{

	string temp = "";
	for (int i = index ; i < b.size(); i++)
	{
		temp += b[i];
	}
	b = temp;
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
