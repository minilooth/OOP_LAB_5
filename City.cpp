#include "City.h"

City::City() = default;

City::City(const string & title)
{
	title_ = title;
}

void City::setTitle(const string& title)
{
	title_ = title;
}

string City::getTitle() const
{
	return title_;
}

City::~City() = default;
