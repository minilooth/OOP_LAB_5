#pragma once

#include <string>

using namespace std;

class InvalidInputException
{
	string error_;
public:
	InvalidInputException()
	{
		error_ = "��������� ����!";
	}

	const string what() const
	{
		return error_;
	}
};