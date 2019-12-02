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

	char tempchar;
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
int textSize(HTree *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else if(root->pLeft == NULL && root->pRight == NULL)
	{
		return root->_freq;
	}
	else
	{
		return textSize(root->pLeft) + textSize(root->pRight);
	}
}
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
void sortDic(vector<Dictionary> &dictionary, FreqTable table)
{
	for (int i = 0; i < table._char.size(); i++)
	{
		for (int j = 0; j < dictionary.size(); j++)
		{
			if (table._char[i] == dictionary[j]._c)
			{
				swap(dictionary[i], dictionary[j]);
			}
		}
	}
}
void createtxtHeader(TXTHEADER &header, string tree, FreqTable table,string duoifile)
{
	//assign signature

	for (int i = 0; i < duoifile.size() - 1; i++)
	{
		header._type[3-i + -1] = duoifile[i];
	}
	//huffman tree
	int temp = tree.size();

	header._treesize = to_string(temp);
	
	header._tree = new  char[temp];

	for (int i = 0; i < temp; i++)
	{
		header._tree[i] = tree[i];
	}
	//text
//	sortDic(diction, table);
	int sum = 0;
	for (int i = 0; i < table._freq.size(); i++)
	{

//		if(table._char[i] != 'ï' && table._char[i] != '»' && table._char[i] != '¿')
		sum += table._freq[i];
	}

	header._realtextsize = to_string(sum);

//	header._textsize =  to_string(((sum+7)/8)*8);

}

void disposetable(TXTHEADER & header)
{
	if(header._tree != NULL)
	delete[] header._tree;
}
