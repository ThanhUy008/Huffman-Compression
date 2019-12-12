#pragma once
#include "Compression.h"
#include "Huffman.h"
#include "Table.h"
#include <direct.h>
#include "Folder.h"
void UZJFileDecompress(char* infile);
void reconvert(string &b, char &c, HTree *root, int &i, bool &check);
void pop_first(string &s);
void pop_first_n(string &b, int index);
void rebuildHuffman(string &b, HTree *&root);
void FolderDecompress(char *infile);
void reconvert(string &b, char &c, HTree *root, int &i, bool &check);