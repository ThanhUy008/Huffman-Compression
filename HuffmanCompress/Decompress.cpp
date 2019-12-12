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
	if (root != NULL)
	{
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
				reconvert(b, c, root->pLeft, i, check);
			}
			else
			{
				i++;
				reconvert(b, c, root->pRight, i, check);
			}
		}
	}
}

//convert char to binary value

//convert char to binary value and then from that binary value find the suitable char from huffman tree.
void convert(HTree *root,char *c, int n,int &count,int realtextsize, ofstream &fout, string &buffer)
{
	char *output = new char[MAX_BUFFER];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		buffer += bitset<8>(c[i]).to_string();
		char c_buffer = ' ';
		//after reconvert check will change.
		//the first init just to make to loop start.
		bool check = true;
		while (check)
		{
			if (count >= realtextsize) break;
			int index = 0;

			reconvert(buffer, c_buffer, root, index, check);
			if (check)
			{
				//remove binary value of the char we have found
				buffer.erase(0, index);
				//consider finding another char
				count++;
				if (j > MAX_BUFFER - 1) //if buffer is full
				{
					//write it out
					fout.write(output, MAX_BUFFER);
					//reset j
					j = 0;
					//rewrite the buffer 
					output[j] = c_buffer;
					j++;
				}
				else
				{
					//write newly found char to buffer
					output[j] = c_buffer;
					j++;
				}
				
			}
		}
	}
	//if the buffer isn't empty
	//write it to output
	if (j != 0)
	{
		fout.write(output, j);
	}
	delete[] output;
}



void UZJFileDecompress(char* infile)
{
	ifstream inFILE;
	
	
	inFILE.open(infile,ios::binary);
	if (inFILE.fail())
	{
		cout << "CANT OPEN UZIP FILE";
		exit(0);
	}
	char *tmp = new char[MAX_BUFFER];
	inFILE.seekg(0, ios::end);
	long long length = inFILE.tellg();
	inFILE.seekg(0, ios::beg);
	//lay chu signature txt, exe,cpp ...;
	string duoifile;
	char trash;
	//remove the .uzj
	for (int i = 0; i < 3; i++)
	{
		inFILE >> noskipws >> trash;
		duoifile.push_back(trash);
	}

	//remove .uzj in zip file
	string outfilename(infile);
	for (int i = 0; i < 4; i++)
		outfilename.pop_back();
	
	//add new .txt, .exe , etc...
	//name it again
	outfilename += "-decompress." + duoifile;

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
	for(int i = 0 ; i < Treesize ;i++)
	{
		inFILE >> noskipws >> trash;
		saveTree.push_back(trash);
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

	//get the text size
	while (inFILE.peek() != '/')
	{
		char temp;
		inFILE >> noskipws >> temp;
		header._textsize.push_back(temp);
	}

	//dipose the last '/'
	inFILE >> noskipws >> trash;

	//this does nothing
	header._tree = NULL;

	//convert string to int
	int realtextsize = stoi(header._realtextsize);
	int textsize = stoi(header._textsize);

	//rebuild Huffman Tree
	HTree* root = NULL;
	rebuildHuffman(saveTree, root);
	//var to save input char
	char temp;

	//var to save binary of char after convert
	string buffer = "";
	
	//var to check if enough char
	int count = 0;
	//loop until end of file
	while (length > 0)
	{
		inFILE.read(tmp, MAX_BUFFER);
		length -= MAX_BUFFER;
		int n;
		if (length < 0) n = MAX_BUFFER + length;
		else n = MAX_BUFFER;

		convert(root, tmp, n, count, realtextsize, outFILE, buffer);
		
	}
	delete[] tmp;


	//if there is a spare char, remove it
	
	if (textsize != 0)
	{
		inFILE >> noskipws >> trash;
	}

	disposetable(header);
	depose(root);
	inFILE.close();
	outFILE.close();
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
				b.erase(0, 1);

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
				b.erase(0, 2);
				//jump to node right
			}
		}
	}
}
