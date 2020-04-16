#pragma once

#include <string>

using namespace std;

class BankAlreadyExistsException
{
	string error_;
public:
	BankAlreadyExistsException()
	{
		error_ = "Банк уже существует!";
	}

	const string what() const
	{
		return error_;
	}
};