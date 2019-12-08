#include "Compression.h"

void emptyfyString(string &in)
{
	while (!in.empty())
	{
		in.pop_back();
	}
}
bool checkenough(string in)
{
	if (in.size() < 8) return false;
	return true;
}
//des empty
void copybyte(string &des, string &in)
{
	for (int i = 0; i < 8; i++)
	{
		des.push_back(in[i]);
	}
	string temp = "";
	for (int i = 8; i < in.size(); i++)
	{
		temp.push_back(in[i]);
	}
	in = temp;
}
void converttobinary(HTree *root, string &binary, int freq)
{
	if (binary.size() >= 8)
	{
		//TODO: WRITE TO FILE
		//EMPTY BINARY
	}
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->pLeft != NULL && root->pRight != NULL)
		{
			if (root->pLeft->_freq == freq)
			{
				binary += '0';
			}
			else if (root->pRight->_freq == freq)
			{
				binary += '1';
			}
			else
			{
				int left = root->pLeft->_freq;
				int right = root->pRight->_freq;

			}
		}
	}
}
char binarytochar(string &b)
{
	char c;
	c = c & 0x00;
	for (int i = 0; i < 8; i++)
	{
		if (b[i] == '1')
		{
			c ^= 0x01;
		}
		if (i != 7) c <<= 1;
	}
	b.erase(0, 8);
	return c;
}
string chartobinary(char c)
{
	string b = "";
	for (int i = 0; i < 8; i++)
	{
		if ((c & 0x80) == 0x80)
		{
			b.push_back('1');
		}
		else b.push_back('0');
	}
	return b;
}
void convertting(vector<Dictionary> dic, char *b, long long n, ofstream &out, FreqTable table, string &binary_temp)
{
	int j = 0;
	string binary_value = "";
	char *tmp = new char[MAX_BUFFER];
	for (long long i = 0; i < n; i++)
	{
		int k =  char(b[i]) + 128;
		int pos = table._freq[k];

		binary_temp += dic[pos]._binary;

		while (binary_temp.size() >= 8)
		{
			char c = binarytochar(binary_temp);
			if (j > MAX_BUFFER - 1)
			{
				out.write(tmp, j);
				j = 0;
				tmp[j] = c;
				j++;
			}
			else
			{
				tmp[j] = c;
				j++;
			}

		}
	}
	if (j != 0)
	{
		out.write(tmp, j);
	}
	delete[] tmp;
}

//can zip every file can be read in binary
void UZIP(char* infile)
{
	ifstream inFile;

	string outfilename(infile);
	string duoifile = "";
	for (int i = 0; i < 4; i++)
	{
		duoifile += outfilename[outfilename.size() - 1];
		outfilename.pop_back();
	}
	outfilename += ".uzip";
	//create output
	ofstream outFILE;
	outFILE.open(outfilename.c_str(),ios::binary);

	FreqTable freqtable;
	TXTHEADER header;
	Dictionary t_dictionary;
	vector<Dictionary> dictionary;

	vector<HTree*> leafnode = handleInputFile(infile, freqtable);
	HTree* root = creatHuffmanTree(leafnode);

	string saveTree = "";
	creatsaveTree(root, saveTree);

	initDistionary(root, t_dictionary, dictionary);

	createtxtHeader(header, saveTree, freqtable,duoifile);

	//write header to outfile
	if (outFILE.fail())
	{
		cout << "can't create output";
		exit(0);
	}

	outFILE.write(header._type, 3);

	outFILE << '/';

	outFILE.write(header._treesize.c_str(), header._treesize.size());

	outFILE << '/';


	outFILE.write(header._tree, atoi(header._treesize.c_str()));

	outFILE << '/';

	outFILE.write(header._realtextsize.c_str(), header._realtextsize.size());

	outFILE << '/';

	sortDic(dictionary, freqtable);
	//convert all char
	string binary_temp = "";
	inFile.open(infile,ios::binary);
	if (inFile.fail())
	{
		cout << "can't open input";
		exit(0);
	}
	inFile.seekg(0, ios::end);
	long long length = inFile.tellg();
	inFile.seekg(0, ios::beg);

	char *c_temp = new char[MAX_BUFFER];
	while (length > 0)
	{
		inFile.read(c_temp, MAX_BUFFER);
		length -= MAX_BUFFER;
		long long n;
		if (length < 0)
		{
			n = length + MAX_BUFFER;
		}
		else
		{
			n = MAX_BUFFER;
		}
		convertting(dictionary, c_temp, n, outFILE,freqtable,binary_temp);
		

	}
	delete[] c_temp;
	if (binary_temp.size() != 0)
	{
		while (binary_temp.size() < 8)
		{
			binary_temp.push_back('0');
		}
		char c = binarytochar(binary_temp);
		outFILE << c;
	}
	
	inFile.close();
	outFILE.close();
	depose(root);
	disposetable(header);

}



