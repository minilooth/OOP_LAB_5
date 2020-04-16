#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <Windows.h>

#include "BankHandler.h"

using namespace std;

enum class EmployeeEditMenuAction
{
	EDIT_FIRSTNAME = 1,
	EDIT_SURNAME,
	EDIT_TELEPHONE,
	EDIT_POSITION,
	BACK_TO_BANK_MENU
};

enum class BankEditMenuAction
{
	EDIT_TITLE = 1,
	EDIT_CITY,
	BACK_TO_MAIN_MENU
};

enum class MainMenuAction
{
	CHOOSE_BANK = 1,
	ADD_BANK,
	DELETE_BANK,
	EDIT_BANK,
	SHOW_BANKS,
	SORT_BANKS,
	FIND_BANK,
	QUIT
};

enum class BankMenuAction
{
	ADD_EMPLOYEE = 1,
	DELETE_EMPLOYEE,
	EDIT_EMPLOYEE,
	SHOW_EMPLOYEES,
	SORT_EMPLOYEES,
	FIND_EMPLOYEE,
	BACK_TO_MAIN_MENU
};

MainMenuAction mainMenu();
BankMenuAction bankMenu();
BankEditMenuAction bankEditMenu();
EmployeeEditMenuAction employeeEditMenu();


istream& operator>>(istream& is, MainMenuAction& action);
istream& operator>>(istream& is, BankMenuAction& action);
istream& operator>>(istream& is, BankEditMenuAction& action);
istream& operator>>(istream& is, EmployeeEditMenuAction& action);