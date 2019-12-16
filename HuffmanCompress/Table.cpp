#include "Table.h"
#include <string>
void initDistionary(HTree* huffman, Dictionary &temp, vector<Dictionary> &output)
{
	if (huffman != NULL)
	{
		if (huffman->pLeft == NULL && huffman->pRight == NULL) //if the HTree is have only a character meaning it is the leaf node
										//so we need to add it binary value to the final distionary
		{
			if (temp._binary.size() == 0) //if input string have only 1 digit the huffman tree 'll have only one node
			{							 //and the Distionary temp will be empty, so we init it with '0'
				temp._binary += '0';
			}
			temp._c = huffman->_char; //this is to know which character binary value is
			temp._charfreq = huffman->_freq; // get the freq
			output.push_back(temp); // add it in the final distionary
			temp._binary.pop_back(); //clean the last value of stack so we can continue DFS
		}
		else
		{
			//if huffman isn't the leaf not, we start to look from the left to the right
			//adding '0' to binary value to start search on the left node
			temp._binary += '0';
			initDistionary(huffman->pLeft, temp, output);
			//adding '1' to start search on the right node
			temp._binary += '1';
			initDistionary(huffman->pRight, temp, output);

			//after finishing looking on a branch, we need to clean the last value of stack to continue searching on another branch.
			if (temp._binary.size() > 0)
				temp._binary.pop_back();
		}
	}
}
void createFreqTable(FreqTable &out)
{
	//create a table contain 256 char with the freq of 0
	for (int i = 0; i < 256; i++)
	{
		char temp = char(i - 128);
		out._char.push_back(temp);
		out._freq.push_back(0);
	}
}

void takecare(char *b, long long n, FreqTable &out)
{
	for (long long i = 0; i < n; i++)
	{
		// if buffer[i] exist, add the 1 to the freq of it
		int k = char(b[i]) + 128;
		out._freq[k]++;
	}
}


//create the freqtable to create huffman tree
vector<HTree*> handleInputFile(char *file, FreqTable &table)
{
	vector<HTree*> tree;
	ifstream inFile;
	inFile.open(file, ios::binary);
	if (inFile.fail())
	{
		cout << "cant open file";
		exit(0);
	}

	//get length of file
	inFile.seekg(0, ios::end);
	long long length = inFile.tellg();
	inFile.seekg(0, ios::beg);
	
	createFreqTable(table);
	char *tempchar = new char[MAX_BUFFER];

	while (length > 0)
	{
		inFile.read(tempchar, MAX_BUFFER);
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
		takecare(tempchar, n, table);
	}
	delete[] tempchar;

	//create the very first node of huffman tree
	for (int i = 0; i < table._freq.size(); i++)
	{
		HTree *temp;
		initTree(temp);
		if (table._freq[i] != 0) // if exist in file, create that node
		{
			push(temp, table._char[i], table._freq[i]);
			tree.push_back(temp);
		}
	}
	inFile.close();
	return tree;

}

//create string to save huffman tree to decompress
void creatsaveTree(HTree *in, string &temp)
{
	if (in != NULL)
	{
		if (in->pLeft == NULL && in->pRight == NULL)
		{
			temp.push_back('1');
			temp.push_back(in->_char);
		}
		else
		{
			temp.push_back('0');
			creatsaveTree(in->pLeft, temp);

			creatsaveTree(in->pRight, temp);
		}
	}
}

//write the position of char in dictionary to freq of FreqTable
//to make the finding binary value faster
void sortDic(vector<Dictionary> &dictionary, FreqTable &table)
{
	for (int i = 0; i < table._char.size(); i++)
	{
		if (table._freq[i] != 0)
		{
			for (int j = 0; j < dictionary.size(); j++)
			{
				if (table._char[i] == dictionary[j]._c)
				{
					table._freq[i] = j;
					break;
				}
			}
		}
	}
}



void createtxtHeader(TXTHEADER &header, string tree, vector<Dictionary> dic,string duoifile)
{
	//assign signature
	if (duoifile.size() < 3)
		while (duoifile.size() < 3)
			duoifile.push_back('#');

	header._type[0] = duoifile[0];

	header._type[1] = duoifile[1];

	header._type[2] = duoifile[2];
	//huffman tree
	int temp = tree.size();

	header._treesize = to_string(temp);
	
	header._tree = new  char[temp];

	for (int i = 0; i < temp; i++)
	{
		header._tree[i] = tree[i];
	}
	//text

	int sum = 0;
	unsigned long bisum = 0;
	for (int i = 0; i < dic.size(); i++)
	{

		sum += dic[i]._charfreq;
		bisum += dic[i]._charfreq *dic[i]._binary.size();
	}

	header._realtextsize = to_string(sum);

	//check if there is spare char, meaning the binary value if not % 8 = 0, so we will add another char to the end of file

	if (bisum % 8 != 0)
	{
		header._textsize = to_string(1);
		header._numberofcharaftercompress = to_string((bisum / 8) + 1);
	}
	else
	{
		header._numberofcharaftercompress = to_string((bisum / 8));
		header._textsize = to_string(0);
	}

}

void disposetable(TXTHEADER & header)
{
	if(header._tree != NULL)
	delete[] header._tree;
}
