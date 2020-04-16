#pragma once

#include <string>

using namespace std;

class BankNotFoundException
{
	string error_;
public:
	BankNotFoundException()
	{
		error_ = "Банк не найден!";
	}

	const string what() const
	{
		return error_;
	}
};