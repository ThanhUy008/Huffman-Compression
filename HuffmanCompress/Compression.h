#pragma once
#include "Huffman.h"
#include "Table.h"
#include "Folder.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

//


//compress a folder
void FolderCompress(vector<FILESAVE> v, string dir);
//compress file in folder
void filecompress(char* infile, ofstream &outFILE, string filename);
//des empty
//


//compress single folder
void UZJtext(char* infile);
