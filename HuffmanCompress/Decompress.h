#pragma once
#include "Compression.h"
#include "Huffman.h"
#include "Table.h"

string readTXTheader(char* infile);
void pop_first(string &s);
void rebuildHuffman(string &b, HTree *&root);
