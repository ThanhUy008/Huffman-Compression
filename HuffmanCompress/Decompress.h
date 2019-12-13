#pragma once
#include "Compression.h"
#include "Huffman.h"
#include "Table.h"
#include <direct.h>
#include "Folder.h"

//decompress a single file
void UZJFileDecompress(char* infile);
//get char from huffman tree
void reconvert(string &b, char &c, HTree *root, int &i, bool &check);
//rebuild the huffman tree
void rebuildHuffman(string &b, HTree *&root);
//compress a folder
void FolderDecompress(char *infile);
