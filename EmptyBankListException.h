#pragma once

#include <string>

using namespace std;

class EmptyBankListException
{
	string error_;
public:
	EmptyBankListException()
	{
		error_ = "������ ������ ����!";
	}

	const string what()
	{
		return error_;
	}
};