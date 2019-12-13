#include "Huffman.h"
#include "Table.h"
#include "Compression.h"
#include "Decompress.h"
#include "Folder.h"
#include <direct.h>
#define DIR_SAMPLE "C:\\Users\\User\\Desktop"
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
	if (in == "Exit") return 0;
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
	string filename;
	int n = EvalueStr(in);
	switch (n)
	{
	case 1:
		cout << "ENTER FILE NAME " << endl;
		getline(cin >>  ws,filename);
		UZJFileDecompress((char*)filename.c_str());
		cout << "COMPLETED" << endl;
		break;
	case 2:
		cout << "ENTER FILE NAME " << endl;
		getline(cin >> ws, filename);
		FolderDecompress((char*)filename.c_str());
		cout << "COMPLETED" << endl;
		break;
	case 0:
		return;
	}
}

void Compress(string in)
{
	string filename;

	vector<FILESAVE> temp;

	int n = EvalueStr(in);
	switch (n)
	{
	case 1:
		cout << "ENTER FILE NAME " << endl;
		getline(cin >> ws, filename);
		UZJtext((char*)filename.c_str());
		cout << "COMPRESS COMPLETED " << endl;
		break;
	case 2:
		cout << "ENTER PATH NAME, REMEMBER, PATH MUST LOOK LIKE THIS  < C:\\User\\Desktop > " << endl;
		getline(cin >> ws, filename);
		read_directory(filename, temp);
		FolderCompress(temp, filename);
		cout << "COMPRESS COMPLETED " << endl;
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
			return;
		default:
			break;
		}
		cout << "Do you want to continue , type 1 to conitune, type 0 to stop \n";
		
		cin >> wantmore;

	} while (wantmore);


}
