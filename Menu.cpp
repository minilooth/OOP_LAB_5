#include "Menu.h"

MainMenuAction mainMenu()
{
	MainMenuAction action;

	while (true)
	{
		try
		{
			system("cls");
			cout << "Главное меню: " << endl;
			cout << "1 - Выбрать банк." << endl;
			cout << "2 - Добавить банк." << endl;
			cout << "3 - Удалить банк." << endl;
			cout << "4 - Редактировать банк." << endl;
			cout << "5 - Показать все банки." << endl;
			cout << "6 - Сортировать банки." << endl;
			cout << "7 - Найти банк." << endl;
			cout << "8 - Выход." << endl;
			cout << "Ваш выбор: ";
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
			cout << "Банковское меню: " << endl;
			cout << "1 - Добавить сотрудника." << endl;
			cout << "2 - Удалить сотрудника." << endl;
			cout << "3 - Редактировать сотрудника." << endl;
			cout << "4 - Показать сотрудников." << endl;
			cout << "5 - Сортировать сотрудников." << endl;
			cout << "6 - Найти сотрудника." << endl;
			cout << "7 - Вернуться в главное меню." << endl;
			cout << "Ваш выбор: ";
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
			cout << "Меню редактирования банка: " << endl;
			cout << "1 - Редактировать наименование банка." << endl;
			cout << "2 - Редактировать город банка." << endl;
			cout << "3 - Вернуться в главное меню." << endl;
			cout << "Ваш выбор: ";
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
			cout << "Меню редактирования сотрудника: " << endl;
			cout << "1 - Редактировать имя сотрудника." << endl;
			cout << "2 - Редактировать фамилию сотрудника." << endl;
			cout << "3 - Редактировать телефон сотрудника." << endl;
			cout << "4 - Редактировать должность сотрудника." << endl;
			cout << "5 - Вернуться в банковское меню." << endl;
			cout << "Ваш выбор: ";
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
