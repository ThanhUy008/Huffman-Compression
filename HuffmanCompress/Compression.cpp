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
	string binary_value = "";
	string binary_temp = "";
	inFile.open(infile,ios::binary);
	if (inFile.fail())
	{
		cout << "can't open input";
		exit(0);
	}

	char c_temp;
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

		while (checkenough(binary_temp))
		{
			copybyte(binary_value, binary_temp);
			char c = strtol(binary_value.c_str(), 0, 2);
			outFILE.write(&c, 1);
			emptyfyString(binary_value);
		}

	}

	if (binary_temp.size() != 0)
	{
		while (binary_temp.size() < 8)
			binary_temp += '0';
		char c = strtol(binary_temp.c_str(), 0, 2);
		outFILE.write(&c, 1);
	}

	inFile.close();
	outFILE.close();
	depose(root);
	disposetable(header);

}



