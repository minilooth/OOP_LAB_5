#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <regex>

#include "City.h"
#include "Employee.h"
#include "Menu.h"

#include "EmptyEmployeesListException.h"
#include "EmployeeNotFoundException.h"
#include "InvalidInputException.h"

using namespace std;

class Bank
{
	string title_;
	City city_;
	multimap<unsigned, Employee> employees_;
	static pair<unsigned, Employee*> editableEmployee_;

	void editFirstname();
	void editSurname();
	void editTelephone();
	void editPosition();
public:
	Bank();
	Bank(const string& title, const City& city);
	Bank(const string& title, const City& city, const multimap<unsigned, Employee>& employees);

	void setTitle(const string& title);
	void setCity(const City& city);
	void setEmployees(const multimap<unsigned, Employee>& employees);

	string getTitle() const;
	City getCity() const;
	multimap<unsigned, Employee> getEmployees() const;

	unsigned getEmployeeId(Employee* employee);

	void addEmployee();
	void deleteEmployee();
	void editEmployee();
	void showEmployees();
	static void showEditableEmployee();
	void findEmployee();
	void sortEmployees();
	void writeInTxt();
	void readFromTxt();

	~Bank();
};

