#pragma once
#include "Compression.h"
#include <iostream>
#include <algorithm>
#include <Windows.h>


#include <locale>
#include <codecvt>
using namespace std;

//get the files name in folder
void read_directory(string name, vector<FILESAVE> & v);
//get a folder name in directory
string getFolderName(string dir);

