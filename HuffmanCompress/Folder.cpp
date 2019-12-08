#include "Folder.h"

void read_directory(string name, vector<wstring> & v)
{
std::string pattern(name);
pattern.append("\\*");
WIN32_FIND_DATA data;
HANDLE hFind;
hFind = FindFirstFile(LPCWSTR(pattern.c_str()), &data);
if (hFind != INVALID_HANDLE_VALUE)
{
	do {
		string temp;
		std::wstring savedata(data.cFileName);
		v.push_back(data.cFileName);
	} while (FindNextFile(hFind, &data) != 0);
	FindClose(hFind);
}
}
