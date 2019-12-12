#pragma once
#include "Huffman.h"
#include "Table.h"
#include "Folder.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
void emptyfyString(string &in);
bool checkenough(string in);
void FolderCompress(vector<FILESAVE> v, string dir);
void filecompress(char* infile, ofstream &outFILE, string filename);
//des empty
void copybyte(string &des, string &in);
void UZJtext(char* infile);
