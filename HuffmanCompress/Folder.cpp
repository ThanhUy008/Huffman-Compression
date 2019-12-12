#include "Folder.h"

string ConverWstrToStr(wstring input)
{
	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string converted_str = converter.to_bytes(input);
	return converted_str;
}
bool isTrash(string filename)
{
	if (filename == "." || filename == "..") return true;
	return false;
}
bool checkiffolder(string filename)
{
	if (filename == "." || filename == "..") return false;
	if (filename.size() < 5)
	{
		return true;
	}
	else
	{
		char c = filename[filename.size() - 1 - 3];
		if (c == '.') return false;
		else return true;
	}
}
//C:\\DATA
string getFolderName(string dir)
{
	
	string result = "";
	for (int i = dir.size() - 1; i >= 0; i--)
	{
		if (dir[i] == '\\') break;
		else
		{
			result += dir[i];
		}
	}
	reverse(result.begin(), result.end());
	return result;
}
void read_directory(string name, vector<FILESAVE> & v)
{
	FILESAVE filesave;
	string curfoldername = getFolderName(name);
	filesave.isFoler = true;
	filesave.name = curfoldername;

	v.push_back(filesave);

	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATAA data;
	HANDLE hFind;
	hFind = FindFirstFileA((pattern.c_str()), &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			string temp = (data.cFileName);
			if (!isTrash(temp))
			{
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					filesave.isFoler = true;
					filesave.name = temp;
				}
				else
				{
					filesave.isFoler = false;
					filesave.name = temp;
				}
				v.push_back(filesave);
			}
		} while (FindNextFileA(hFind, &data) != 0);


		FindClose(hFind);
	}
	


}

//vector<string> get_all_files_names_within_folder(string folder)
//{
//	vector<string> names;
//	string search_path = folder + "/*.*";
//	WIN32_FIND_DATA fd;
//	HANDLE hFind = ::FindFirstFile(LPCWSTR(search_path.c_str()), &fd);
//	if (hFind != INVALID_HANDLE_VALUE) {
//		do {
//			// read all (real) files in current folder
//			// , delete '!' read other 2 default folder . and ..
//			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//				names.push_back(fd.cFileName);
//			}
//		} while (::FindNextFile(hFind, &fd));
//		::FindClose(hFind);
//	}
//	return names;
//}