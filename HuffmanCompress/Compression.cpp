#include "Compression.h"


string findDuoifile(string &in)
{
	string result = "";
	for (int i = in.size() - 1; i >= 0; i--)
	{
		if (in[i] == '.')
		{
			in.pop_back();
			break;
		}
		else
		{
			result.push_back(in[i]);
			in.pop_back();
		}
	}
	reverse(result.begin(), result.end());
	return result;
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
//convert binary value to char
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

//convert char to binary value

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

//convert all char in buffer to the suitable binary value acording to huffman
//convert tha binary value to char and write it to file
void convertting(vector<Dictionary> dic, char *b, long long n, ofstream &out, FreqTable table, string &binary_temp)
{
	int j = 0;
	string binary_value = "";
	char *tmp = new char[MAX_BUFFER];
	for (long long i = 0; i < n; i++)
	{
		//find the positon of char in dictionnary
		int k =  char(b[i]) + 128;
		int pos = table._freq[k];
		//get the binary value
		binary_temp += dic[pos]._binary;

		while (binary_temp.size() >= 8)
		{
			char c = binarytochar(binary_temp);
			//if buffer is full, write it to outfile and then re use the buffer again
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
	//if buffer isn't empty, write it to outfile
	if (j != 0)
	{
		out.write(tmp, j);
	}
	delete[] tmp;
}

void writeheadertofile(TXTHEADER header,ostream &outFILE)
{
	outFILE.write(header._type, 3);


	if (!header._filename.empty())
	{
		outFILE.write(header._filename.c_str(), header._filename.size());

		outFILE << '/';

	}

	outFILE.write(header._treesize.c_str(), header._treesize.size());

	outFILE << '/';


	outFILE.write(header._tree, atoi(header._treesize.c_str()));

	outFILE << '/';

	outFILE.write(header._realtextsize.c_str(), header._realtextsize.size());

	outFILE << '/';

	outFILE.write(header._textsize.c_str(), header._textsize.size());

	outFILE << '/';

	outFILE.write(header._numberofcharaftercompress.c_str(),header._numberofcharaftercompress.size());

	outFILE << '/';
}

void recruiteFolderCompress(string dir, ofstream &fout)
{
	vector<FILESAVE>v;

	read_directory(dir,v);

	FOLDERHEADER header;
	header._type[0] = 'f';
	header._type[1] = 'o';
	header._type[2] = 'l';
	
	header._foldername = v[0].name;

	header._numberoffile = to_string(v.size() - 1);

	fout.write(header._type, 3);
	

	fout.write(header._foldername.c_str(), header._foldername.size());

	fout << '/';

	fout.write(header._numberoffile.c_str(), header._numberoffile.size());

	fout << '/';

	for (int i = 1; i < v.size(); i++)
	{
		if (!v[i].isFoler)
		{
			string tmp = dir + '\\' + v[i].name;
			filecompress((char*)tmp.c_str(), fout,v[i].name);
		}
		else
		{
			string temmp = dir + '\\' + v[i].name;
			recruiteFolderCompress(temmp,fout);
		}
	}
}

void FolderCompress(vector<FILESAVE> v,string dir)
{
	string name = v[0].name + ".uzj";
	ofstream fout(name,ios::binary);
	recruiteFolderCompress(dir, fout);
}
void filecompress(char* infile, ofstream &outFILE, string filename)
{

	ifstream inFile;

	string outfilename(infile);

	string duoifile = findDuoifile(outfilename);
	
	outfilename += ".uzj";
	

	FreqTable freqtable;
	TXTHEADER header;
	Dictionary t_dictionary;
	vector<Dictionary> dictionary;
	//build huffman tree
	vector<HTree*> leafnode = handleInputFile(infile, freqtable);
	HTree* root = creatHuffmanTree(leafnode);

	//create a string to save huffman tree to decompress
	string saveTree = "";
	creatsaveTree(root, saveTree);

	//create dictionary
	initDistionary(root, t_dictionary, dictionary);

	//write the position of char in in dictionary to freqtable
	sortDic(dictionary, freqtable);

	createtxtHeader(header, saveTree, dictionary, duoifile);

	
	header._filename = filename;
	
	//write header to outfile
	if (outFILE.fail())
	{
		cout << "can't create output";
		exit(0);
	}

	writeheadertofile(header, outFILE);


	string binary_temp = "";

	inFile.open(infile, ios::binary);
	if (inFile.fail())
	{
		cout << "can't open input";
		exit(0);
	}
	//get the length of file
	inFile.seekg(0, ios::end);
	long long length = inFile.tellg();
	inFile.seekg(0, ios::beg);

	char *c_temp = new char[MAX_BUFFER];
	while (length > 0) // loop until eof
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
		convertting(dictionary, c_temp, n, outFILE, freqtable, binary_temp);


	}
	delete[] c_temp;

	//if there is a spare binary value that is not enough 8 bit, add '0' until it reach 8
	//then write the last char to outfile
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
	t_dictionary._binary.clear();
	dictionary.clear();
	saveTree.clear();
	depose(root);
	disposetable(header);

}

//can zip every file can be read in binary
void UZJtext(char* infile)
{
	ifstream inFile;

	string outfilename(infile);
	string duoifile = findDuoifile(outfilename);
	outfilename += ".uzj";
	//create output
	ofstream outFILE;


	FreqTable freqtable;
	TXTHEADER header;
	Dictionary t_dictionary;
	vector<Dictionary> dictionary;
	//build huffman tree
	vector<HTree*> leafnode = handleInputFile(infile, freqtable);
	HTree* root = creatHuffmanTree(leafnode);

	outFILE.open(outfilename.c_str(), ios::binary);

	//create a string to save huffman tree to decompress
	string saveTree = "";
	creatsaveTree(root, saveTree);

	//create dictionary
	initDistionary(root, t_dictionary, dictionary);

	//write the position of char in in dictionary to freqtable
	sortDic(dictionary, freqtable);

	createtxtHeader(header, saveTree, dictionary,duoifile);

	//write header to outfile
	if (outFILE.fail())
	{
		cout << "can't create output";
		exit(0);
	}

	writeheadertofile(header, outFILE);
	
	
	string binary_temp = "";
	
	inFile.open(infile,ios::binary);
	if (inFile.fail())
	{
		cout << "can't open input";
		exit(0);
	}
	//get the length of file
	inFile.seekg(0, ios::end);
	long long length = inFile.tellg();
	inFile.seekg(0, ios::beg);

	char *c_temp = new char[MAX_BUFFER];
	while (length > 0) // loop until eof
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
	 
	//if there is a spare binary value that is not enough 8 bit, add '0' until it reach 8
	//then write the last char to outfile
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



