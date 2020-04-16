#pragma once

#include <string>

using namespace std;

class EmptyEmployeesListException
{
	string error_;
public:
	EmptyEmployeesListException()
	{
		error_ = "Список сотрудников пуст!";
	}

	const string what() const
	{
		return error_;
	}
};