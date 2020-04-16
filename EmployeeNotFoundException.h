#pragma once

#include <string>

using namespace std;

class EmployeeNotFoundException
{
	string error_;
public:
	EmployeeNotFoundException()
	{
		error_ = "Сотрудник не найден!";
	}

	const string what() const
	{
		return error_;
	}
};