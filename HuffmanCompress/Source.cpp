#include "Huffman.h"
#include "Table.h"
#include "Compression.h"
#include "Decompress.h"
#include "Folder.h"
#include <comdef.h>  // you will need this
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
void read(char* file1)
{
	ifstream FILE1;
	FILE1.open(file1, ios::binary);

	char temp1, temp2;
	while (FILE1 >> noskipws >> temp1)
	{
		cout << temp1;
	}

}
void main()
{
	
	UZIP("corpus-title.txt");
	Decompression("corpus-title.uzip");
	//TODO : MAKE A MENU
}
