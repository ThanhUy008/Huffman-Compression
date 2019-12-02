#pragma once
#include "Compression.h"
#include "Huffman.h"
#include "Table.h"

void Decompression(char* infile);
void pop_first(string &s);
void reconvert(string &b, char &c, HTree *root, int &i);
void pop_first_8(string &b);
void pop_first_n(string &b, int index);
void rebuildHuffman(string &b, HTree *&root);
