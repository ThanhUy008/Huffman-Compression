#include "Huffman.h"
#include "Table.h"
#include "Compression.h"
#include "Decompress.h"
#include "Folder.h"

void PrintHeader()
{
	cout << "       _________                                            |  " << endl;
	cout << "      /     ____|                                           | " << endl;
	cout << "      |    |        ______________    _________             | " << endl;
	cout << "      |    |       /   __    __   |  /    _    |            | " << endl;
	cout << "      |    |       |  |  |  |  |  |  |   |_|   |            | " << endl;
	cout << "      |    |_____  |  |  |  |  |  |  |    ____/             | "<< endl;
	cout << "      |_________/  |__|  |__|  |__|  |   |                  | " << endl;
	cout << "                                     |   |                  | " << endl;
	cout << "                                     |___|                  | " << endl;


}

int EvalueStrInPut(string in)
{
	if (in == "Compress")
		return 1;
	if (in == "Decompress")
		return 2;
	if(in == "Exit")
	return 0;
}

int EvalueStr(string in)
{
	if (in == "Folder")
		return 2;
	if (in == "File")
		return 1;
	return 0;
}

void Decompress(string in)
{
	char filename[1024];
	int n = EvalueStr(in);
	switch (n)
	{
	case 1:
		cout << "ENTER FILE NAME " << endl;
		cin >> filename;
		UZJFileDecompress(filename);
		break;
	case 2:
		cout << "NOT AVAILABLE AT THE MOMENT" << endl;
		break;
	case 0:
		return;
	}
}

void Compress(string in)
{
	char filename[1024];
	int n = EvalueStr(in);
	switch (n)
	{
	case 1:
		cout << "ENTER FILE NAME " << endl;
		cin >> filename;
		UZJtext(filename);
		break;
	case 2:
		cout << "NOT AVAILABLE AT THE MOMENT" << endl;
		break;
	case 0:
		return;
	}
}

void main()
{
	int wantmore = 1;
	string in;
	PrintHeader();
	do
	{
		cout << "WHAT DO YOU WANT ? \n 1.Enter Compress to compress \n 2.Enter Decompress to decompress uzj file \n 3.Enter Exit to exit\n";
		getline(cin >> ws, in);
		int n = EvalueStrInPut(in);
		switch (n)
		{
		case 1:
			cout << "ENTER TYPE OF FILE YOU WANT \n 1.Compress Binary File type File \n 2.Compress Folder type Folder \n";
			getline(cin >> ws, in);
			Compress(in);
			break;
		case 2:
			cout << "ENTER TYPE OF FILE YOU WANT \n 1.Decompress Binary File type File \n 2.Decompress Folder type Folder \n";
			getline(cin >> ws, in);
			Decompress(in);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
		cout << "Do you want to continue , type 1 to conitune, type 0 to stop \n";
		
		cin >> wantmore;

	} while (wantmore);
	
}
