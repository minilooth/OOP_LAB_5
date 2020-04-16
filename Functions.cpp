#include "Functions.h"

vector<string> directory_list(const string path)
{
	vector<string> items;
	for (const auto& entry : filesystem::directory_iterator(path))
	{
		items.push_back(entry.path().filename().string());
	}
	return items;
}

vector<string> string_splitter(string& source, char delimiter)
{
	size_t pos = 0;
	vector<string> tokens;

    while ((pos = source.find(';')) != string::npos)
	{
		tokens.push_back(source.substr(0, pos));
		source.erase(0, pos + 1);
	}
	tokens.push_back(source);

	return tokens;
}

void erase_substring(string& source, const string& erase)
{
	size_t pos = source.find(erase);

	if (pos != string::npos)
	{
		source.erase(pos, erase.length());
	}
}
