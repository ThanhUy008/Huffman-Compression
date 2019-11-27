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
void UZIPtxt(char* infile)
{
	ifstream inFile;

	string outfilename(infile);
	for (int i = 0; i < 4; i++)
		outfilename.pop_back();
	outfilename += ".uzip";
	//create output
	FILE *outFILE;
	outFILE = fopen(outfilename.c_str(), "wb+");

	FreqTable freqtable;
	HEADER header;
	Dictionary t_dictionary;
	vector<Dictionary> dictionary;

	vector<HTree*> leafnode = handleInputFile(infile, freqtable);
	HTree* root = creatHuffmanTree(leafnode);

	string saveTree = "";
	creatsaveTree(root, saveTree);

	initDistionary(root, t_dictionary, dictionary);

	createtxtHeader(header, saveTree, dictionary, freqtable);

	//write header to outfile
	if (outFILE == NULL)
	{
		cout << "can't create output";
		exit(0);
	}
	fwrite(&header, sizeof(header), 1, outFILE);

	//convert txt
	string binary_value = "";
	string binary_temp = "";
	inFile.open(infile);
	if (inFile.fail())
	{
		cout << "can't open input";
		exit(0);
	}

	unsigned char c_temp;
	while (inFile >> noskipws >> c_temp)
	{
		for (int i = 0; i < dictionary.size(); i++)
		{
			if (c_temp == dictionary[i]._c)
			{
				binary_temp += dictionary[i]._binary;
				break;
			}
		}

		if (checkenough(binary_temp))
		{
			copybyte(binary_value, binary_temp);
			char c = strtol(binary_value.c_str(), 0, 2);
			fwrite(&c, sizeof(char), 1, outFILE);
		}

	}
	if (binary_temp.size() != 0)
	{
		while (binary_temp.size() < 8)
			binary_temp += '0';
		char c = strtol(binary_temp.c_str(), 0, 2);
		fwrite(&c, sizeof(char), 1, outFILE);
	}



}



