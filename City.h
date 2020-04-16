#pragma once

#include <string>

using namespace std;

class City
{
	string title_;
public:
	City();
	explicit City(const string& title);

	void setTitle(const string& title);

	string getTitle() const;

	~City();
};

