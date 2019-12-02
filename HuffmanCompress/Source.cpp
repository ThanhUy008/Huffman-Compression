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

	UZIPtxt("Text.txt");
	Decompression("Text.uzip");
	/*compare("Text.txt", "Text1.txt");
	system("pause");*/
}
