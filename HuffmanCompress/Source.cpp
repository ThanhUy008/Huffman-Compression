#include "Huffman.h"
#include "Table.h"
#include "Compression.h"
#include "Decompress.h"
void main()
{

	UZIPtxt("test.txt");
	string saveTree = readTXTheader("test1.uzip");
	HTree *newHuffmanTree = NULL;
	
	rebuildHuffman(saveTree, newHuffmanTree);
}
