#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

vector<string> directory_list(const string path);
vector<string> string_splitter(string& source, char delimiter);
void erase_substring(string& source, const string& erase);
