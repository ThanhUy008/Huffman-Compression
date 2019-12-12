#pragma once
#include "Compression.h"
#include <iostream>
#include <algorithm>
#include <Windows.h>


#include <locale>
#include <codecvt>
using namespace std;

void read_directory(string name, vector<FILESAVE> & v);
string getFolderName(string dir);

