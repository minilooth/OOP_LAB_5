#pragma once

#include <string>

using namespace std;

class BankNotFoundException
{
	string error_;
public:
	BankNotFoundException()
	{
		error_ = "���� �� ������!";
	}

	const string what() const
	{
		return error_;
	}
};