#include "Table.h"

void initDistionary(HTree* huffman, Dictionary &temp, vector<Dictionary> &output)
{
	if (huffman != NULL)
	{
		if (huffman->_char != '#') //if the HTree is have only a character meaning it is the leaf node
										//so we need to add it binary value to the final distionary
		{
			if (temp._binary.size() == 0) //if input string have only 1 digit the huffman tree 'll have only one node
			{							 //and the Distionary temp will be empty, so we init it with '0'
				temp._binary += '0';
			}
			temp._c = huffman->_char; //this is to know which character binary value is
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

	unsigned char tempchar;
	while (inFile >> noskipws >> tempchar)
	{

		int k = findchar(table._char, tempchar);
		if (k == -1)
		{
			table._char.push_back(tempchar);
			table._freq.push_back(1);
		}
		else
		{
			table._freq[k]++;
		}
		
	}
	for (int i = 0; i < table._freq.size(); i++)
	{
		HTree *temp;
		initTree(temp);
		push(temp, table._char[i], table._freq[i]);
		tree.push_back(temp);
	}
	inFile.close();
	return tree;

}
void creatsaveTree(HTree *in, string &temp)
{
	if (in != NULL)
	{
		if (in->pLeft == NULL && in->pRight == NULL)
		{
			temp += '1';
			temp += in->_char;
		}
		else
		{
			temp += '0';
			creatsaveTree(in->pLeft, temp);

			creatsaveTree(in->pRight, temp);
		}
	}
}
void sortDic(vector<Dictionary> &dictionary, FreqTable table)
{
	for (int i = 0; i < dictionary.size(); i++)
	{
		for (int j = 0; j < table._char.size(); j++)
		{
			if (dictionary[i]._c == table._char[j])
			{
				swap(dictionary[i], dictionary[j]);
				break;
			}
		}
	}
}
void createtxtHeader(TXTHEADER &header,string tree,vector<Dictionary> diction,FreqTable table)
{
	//type
	header._type[0] = 't';
	header._type[1] = 'x';
	header._type[2] = 't';
	//table
	header._tabsize = tree.size();
	header._table = new unsigned char[header._tabsize];

	for (int i = 0; i < header._tabsize; i++)
	{
		header._table[i] = tree[i];
	}
	//text
	sortDic(diction, table);
	unsigned int temp = 0;
	for (int i = 0; i < diction.size(); i++)
	{
		temp += diction[i]._binary.size()*table._freq[i];
	}
	header._realtextsize = temp;
	header._textsize = ((temp + 7) / 8) * 8;

}

void disposetable(TXTHEADER & header)
{
	delete[] header._table;
}
