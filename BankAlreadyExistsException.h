#pragma once

#include <string>

using namespace std;

class BankAlreadyExistsException
{
	string error_;
public:
	BankAlreadyExistsException()
	{
		error_ = "���� ��� ����������!";
	}

	const string what() const
	{
		return error_;
	}
};