#include "Menu.h"

MainMenuAction mainMenu()
{
	MainMenuAction action;

	while (true)
	{
		try
		{
			system("cls");
			cout << "������� ����: " << endl;
			cout << "1 - ������� ����." << endl;
			cout << "2 - �������� ����." << endl;
			cout << "3 - ������� ����." << endl;
			cout << "4 - ������������� ����." << endl;
			cout << "5 - �������� ��� �����." << endl;
			cout << "6 - ����������� �����." << endl;
			cout << "7 - ����� ����." << endl;
			cout << "8 - �����." << endl;
			cout << "��� �����: ";
			cin >> action;

			return action;
		}
		catch (InvalidInputException & ex)
		{
			cout << endl << ex.what();
			Sleep(1000);
		}
	}
}

BankMenuAction bankMenu()
{
	BankMenuAction action;

	while (true)
	{
		try
		{
			system("cls");
			cout << "���������� ����: " << endl;
			cout << "1 - �������� ����������." << endl;
			cout << "2 - ������� ����������." << endl;
			cout << "3 - ������������� ����������." << endl;
			cout << "4 - �������� �����������." << endl;
			cout << "5 - ����������� �����������." << endl;
			cout << "6 - ����� ����������." << endl;
			cout << "7 - ��������� � ������� ����." << endl;
			cout << "��� �����: ";
			cin >> action;

			return action;
		}
		catch (InvalidInputException & ex)
		{
			cout << endl << ex.what();
			Sleep(1000);
		}
	}
}

BankEditMenuAction bankEditMenu()
{
	BankEditMenuAction action;

	while (true)
	{
		try
		{
			system("cls");
			BankHandler::showEditableBank();
			cout << "���� �������������� �����: " << endl;
			cout << "1 - ������������� ������������ �����." << endl;
			cout << "2 - ������������� ����� �����." << endl;
			cout << "3 - ��������� � ������� ����." << endl;
			cout << "��� �����: ";
			cin >> action;

			return action;
		}
		catch (InvalidInputException & ex)
		{
			cout << endl << ex.what();
			Sleep(1000);
		}
	}
}

EmployeeEditMenuAction employeeEditMenu()
{
	EmployeeEditMenuAction action;

	while (true)
	{
		try
		{
			system("cls");
			Bank::showEditableEmployee();
			cout << "���� �������������� ����������: " << endl;
			cout << "1 - ������������� ��� ����������." << endl;
			cout << "2 - ������������� ������� ����������." << endl;
			cout << "3 - ������������� ������� ����������." << endl;
			cout << "4 - ������������� ��������� ����������." << endl;
			cout << "5 - ��������� � ���������� ����." << endl;
			cout << "��� �����: ";
			cin >> action;

			return action;
		}
		catch (InvalidInputException & ex)
		{
			cout << endl << ex.what();
			Sleep(1000);
		}
	}
}

istream& operator>>(istream& is, MainMenuAction& action)
{
	string choice;
	is >> choice;

	if (!regex_match(choice, regex("^[0-9]+$")))
	{
		throw InvalidInputException();
	}

	action = static_cast<MainMenuAction>(stoul(choice));

	return is;
}

istream& operator>>(istream& is, BankMenuAction& action)
{
	string choice;
	is >> choice;

	if (!regex_match(choice, regex("^[0-9]+$")))
	{
		throw InvalidInputException();
	}

	action = static_cast<BankMenuAction>(stoul(choice));

	return is;
}

istream& operator>>(istream& is, BankEditMenuAction& action)
{
	string choice;
	is >> choice;

	if (!regex_match(choice, regex("^[0-9]+$")))
	{
		throw InvalidInputException();
	}

	action = static_cast<BankEditMenuAction>(stoul(choice));

	return is;
}

istream& operator>>(istream& is, EmployeeEditMenuAction& action)
{
	string choice;
	is >> choice;

	if (!regex_match(choice, regex("^[0-9]+$")))
	{
		throw InvalidInputException();
	}

	action = static_cast<EmployeeEditMenuAction>(stoul(choice));

	return is;
}
