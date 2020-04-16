#pragma once

#include <string>

using namespace std;

class InvalidInputException
{
	string error_;
public:
	InvalidInputException()
	{
		error_ = "Ошибочный ввод!";
	}

	const string what() const
	{
		return error_;
	}
};