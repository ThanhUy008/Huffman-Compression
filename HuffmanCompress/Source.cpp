#include "Huffman.h"
#include "Table.h"
#include "Compression.h"
#include "Decompress.h"
void compare(char* file1, char * file2)
{
	ifstream FILE1, FILE2;
	FILE1.open(file1,ios::binary);
	FILE2.open(file2,ios::binary);
	char temp1, temp2;
	while (FILE1 >> noskipws >> temp1 && FILE2 >> noskipws >> temp2)
	{
		if (temp1 != temp2)
		{
			cout << "WRONG";
			return;
		}
	}
	cout << " RIGHT";
}
void main()
{
	//UZIP("MTH.exe");
	Decompression("MTH.uzip");
	//compare("Text.txt", "Text1.txt");
	//system("pause");
	/*
	cout << "ENTER THING NEED TO COMPRESS" << endl;;
	
	string input;
	getline(cin >> ws, input);
	char *infile = new char[input.size()];

	strcpy(infile, input.c_str());

	cout << "COMPRESS OR DECOMPRESS \n 1.compress \n 2.decompress" << endl;
	int n;
	cin >> n;
	switch (n)
	{
	case 1:
		UZIP(infile);
		break;
	case 2:
		Decompression(infile);
		break;
	default:
		break;
	}
	delete[] infile;*/
}
