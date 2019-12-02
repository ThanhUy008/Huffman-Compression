#include "Decompress.h"
#include <bitset>
//find char with similar binary value on HTREE
//if c = NULL then cant find
//else c is the char need to find
void reconvert(string &b, char &c, HTree *root, int &i,bool &check)
{
	if(b.empty())
	{
		c = NULL;
		check = false;
		return;
	}
	if (i > b.size())
	{
		c = NULL;
		check = false;
		return;
	}
	if (root->pLeft == NULL && root->pRight == NULL)
	{
		c = root->_char;
		check = true;
		return;
	}
	else
	{
		
		if (b[i] == '0')
		{
			i++;
			reconvert(b, c, root->pLeft, i,check);
		}
		else
		{
			i++;
			reconvert(b, c, root->pRight, i,check);
		}
	}
}

void Decompression(char* infile)
{
	ifstream inFILE;
	
	
	inFILE.open(infile,ios::binary);
	if (inFILE.fail())
	{
		cout << "CANT OPEN UZIP FILE";
		exit(0);
	}
	//lay chu signature txt, exe,cpp ...;
	string duoifile;
	char trash;
	for (int i = 0; i < 3; i++)
	{
		inFILE >> noskipws >> trash;
		duoifile.push_back(trash);
	}

	//remove .uzip in zip file
	string outfilename(infile);
	for (int i = 0; i < 5; i++)
		outfilename.pop_back();
	
	//add new .txt, .exe , etc...
	//TODO : remove the '1' after finish project.
	outfilename += "1." + duoifile;

	ofstream outFILE;
	outFILE.open(outfilename, ios::binary);

	
	TXTHEADER header;
	
	//dispose the '/' after signature

	inFILE >> noskipws >> trash;
	//get huffman tree size
	while (inFILE.peek() != '/')
	{
		char temp;
		inFILE >> noskipws >> temp;
		header._treesize.push_back(temp);
	}

	//dipose the last '/'
	inFILE >> noskipws >> trash;

	//convert string to int
	int Treesize = atoi(header._treesize.c_str());
	
	//get huffman tree
	string saveTree = "";
	for (int i = 0; i < Treesize; i++)
	{
		char c_char;
		inFILE >> noskipws >> c_char;
		saveTree += c_char;
	}
	
	//dipose the last '/'
	inFILE >> noskipws >> trash;

	//get number of char in file
	while (inFILE.peek() != '/')
	{
		char temp;
		inFILE >> noskipws >> temp;
		header._realtextsize.push_back(temp);
	}

	//dipose the last '/'
	inFILE >> noskipws >> trash;

	//this does nothing
	header._tree = NULL;

	//convert string to int
	int realtextsize = stoi(header._realtextsize);
	//rebuild Huffman Tree
	HTree* root = NULL;
	rebuildHuffman(saveTree, root);
	//var to save input char
	char temp;

	//var to save binary of char after convert
	string buffer = "";
	
	//var to check if enough char
	int count = 0;

	while (inFILE >> noskipws >> temp)
	{
		//convert new added char to binary
		buffer += bitset<8>(temp).to_string();
		

		char c_buffer = ' ';
		//after reconvert check will change.
		//the first init just to make to loop start.
		bool check = true;
		while (check)
		{
			if (count >= realtextsize) break;
			int index = 0;
			
			reconvert(buffer, c_buffer, root, index,check);
			if (check)
			{
				pop_first_n(buffer, index);
				outFILE.write(&c_buffer, 1);
				count++;
			}
		}
	}


	disposetable(header);
	depose(root);
	inFILE.close();
	outFILE.close();
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
				root->_char = NULL;
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
