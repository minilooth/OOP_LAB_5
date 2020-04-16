#include "Bank.h"

pair<unsigned, Employee*> Bank::editableEmployee_;

Bank::Bank()
{
	readFromTxt();
}

Bank::Bank(const string & title, const City & city)
{
	title_ = title;
	city_ = city;
	readFromTxt();
}

Bank::Bank(const string & title, const City & city, const multimap<unsigned, Employee> & employees)
{
	title_ = title;
	city_ = city;
	employees_ = employees;
}

void Bank::setTitle(const string& title)
{
	title_ = title;
}

void Bank::setCity(const City& city)
{
	city_ = city;
}

void Bank::setEmployees(const multimap<unsigned, Employee>& employees)
{
	employees_ = employees;
}

string Bank::getTitle() const
{
	return title_;
}

City Bank::getCity() const
{
	return city_;
}

multimap<unsigned, Employee> Bank::getEmployees() const
{
	return employees_;
}

unsigned Bank::getEmployeeId(Employee* employee)
{
	for (auto it = employees_.begin(); it != employees_.end(); it++)
	{
		if (&it->second == employee)
		{
			return it->first;
		}
	}
	return 0;
}

void Bank::writeInTxt()
{
	ofstream employeesData;
	employeesData.open("Data/Employees/" + title_ + "_" + city_.getTitle() + ".txt");

	if (employeesData.is_open())
	{
		for (auto it = employees_.begin(); it != employees_.end(); it++)
		{
			employeesData << it->second.getFirstname() << ";"
				<< it->second.getSurname() << ";"
				<< it->second.getTelephone() << ";"
				<< it->second.getPosition() << endl;
		}
		employeesData.close();
	}
}

void Bank::readFromTxt()
{
	string token;

	string firstname;
	string surname;
	string telephone;
	string position;

	ifstream employeesData;
	employeesData.open("Data/Employees/" + title_ + "_" + city_.getTitle() + ".txt");

	if (employeesData.is_open())
	{
		while (!employeesData.eof())
		{
			if (getline(employeesData, token, '\n'))
			{
				auto data = string_splitter(token, ';');

				firstname = data.at(0);
				surname = data.at(1);
				telephone = data.at(2);
				position = data.at(3);

				employees_.insert(make_pair(employees_.empty() ? 1 : employees_.size() + 1, Employee(firstname, surname, telephone, position)));
			}
		}
		employeesData.close();
	}
}

void Bank::addEmployee()
{
	try
	{
		string firstname;
		cout << "Введите имя нового сотрудника: ";
		cin.ignore();
		getline(cin, firstname);

		if (!regex_match(firstname, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		string surname;
		cout << "Введите фамилию нового сотрудника: ";
		getline(cin, surname);

		if (!regex_match(surname, regex("^[A-Za-zА-Яа-я -]+$")))
		{
			throw InvalidInputException();
		}

		string telephone;
		cout << "Введите телефон нового сотрудника: ";
		getline(cin, telephone);

		if (!regex_match(telephone, regex("^((\\+375)+([0-9]){9})$")))
		{
			throw InvalidInputException();
		}

		string position;
		cout << "Введите должность нового сотрудника: ";
		getline(cin, position);

		if (!regex_match(position, regex("^[A-Za-zА-Яа-я ]+$")))
		{
			throw InvalidInputException();
		}

		employees_.insert(make_pair(employees_.empty() ? 1 : employees_.size() + 1, Employee(firstname, surname, telephone, position)));
		writeInTxt();

		cout << endl << "Сотрудник успешно добавлен!" << endl << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void Bank::deleteEmployee()
{
	try
	{
		if (employees_.empty())
		{
			throw EmptyEmployeesListException();
		}

		showEmployees();

		string id;
		cout << "Введите ид сотрудника для удаления: ";
		cin >> id;

		if (!regex_match(id, regex("^[0-9]+$")))
		{
			throw InvalidInputException();
		}

		auto it = employees_.find(stoul(id));

		if (it == employees_.end())
		{
			throw EmployeeNotFoundException();
		}

		employees_.erase(stoul(id));
		writeInTxt();

		cout << endl << "Сотрудник успешно удален!" << endl << endl;
	}
	catch (EmptyEmployeesListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (EmployeeNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void Bank::editEmployee()
{
	try
	{
		if (employees_.empty())
		{
			throw EmptyEmployeesListException();
		}

		showEmployees();

		string id;
		cout << "Введите ид сотрудника для редактирования: ";
		cin >> id;

		if (!regex_match(id, regex("^[0-9]+$")))
		{
			throw InvalidInputException();
		}

		auto it = employees_.find(stoul(id));

		if (it == employees_.end())
		{
			throw EmployeeNotFoundException();
		}

		editableEmployee_.first = it->first;
		editableEmployee_.second = &it->second;

		while (true)
		{
			switch (employeeEditMenu())
			{
			case EmployeeEditMenuAction::EDIT_FIRSTNAME :
				system("cls");
				editFirstname();
				system("pause");
				break;
			case EmployeeEditMenuAction::EDIT_SURNAME :
				system("cls");
				editSurname();
				system("pause");
				break;
			case EmployeeEditMenuAction::EDIT_TELEPHONE :
				system("cls");
				editTelephone();
				system("pause");
				break;
			case EmployeeEditMenuAction::EDIT_POSITION :
				system("cls");
				editPosition();
				system("pause");
				break;
			case EmployeeEditMenuAction::BACK_TO_BANK_MENU :
				editableEmployee_.second = nullptr;
				return;
			default:
				break;
			}
		}
	}
	catch (EmptyEmployeesListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
		system("pause");
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
		system("pause");
	}
	catch (EmployeeNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
		system("pause");
	}
}

void Bank::showEmployees()
{
	try
	{
		if (employees_.empty())
		{
			throw EmptyEmployeesListException();
		}

		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
		cout << "|  Ид  |       Имя       |      Фамилия     |     Телефон     |       Должность       |" << endl;
		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;

		for (auto it = employees_.begin(); it != employees_.end(); it++)
		{
			cout << "|" << setw(6) << left << it->first;
			cout << "|" << setw(17) << left << it->second.getFirstname();
			cout << "|" << setw(18) << left << it->second.getSurname();
			cout << "|" << setw(17) << left << it->second.getTelephone();
			cout << "|" << setw(23) << left << it->second.getPosition() << "|" << endl;
		}

		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
	}
	catch (EmptyEmployeesListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void Bank::showEditableEmployee()
{
	cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
	cout << "|  Ид  |       Имя       |      Фамилия     |     Телефон     |       Должность       |" << endl;
	cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;

	cout << "|" << setw(6) << left << editableEmployee_.first;
	cout << "|" << setw(17) << left << editableEmployee_.second->getFirstname();
	cout << "|" << setw(18) << left << editableEmployee_.second->getSurname();
	cout << "|" << setw(17) << left << editableEmployee_.second->getTelephone();
	cout << "|" << setw(23) << left << editableEmployee_.second->getPosition() << "|" << endl;

	cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
}

void Bank::findEmployee()
{
	try
	{
		if (employees_.empty())
		{
			throw EmptyEmployeesListException();
		}

		string position;
		cout << "Введите должность для поиска: ";
		cin.ignore();
		getline(cin, position);

		if (!regex_match(position, regex("^[A-Za-zА-Яа-я ]+$")))
		{
			throw InvalidInputException();
		}

		map<unsigned, Employee> result;

		for (auto it = employees_.begin(); it != employees_.end(); it++)
		{
			if (it->second.getPosition() == position)
			{
				result.insert(make_pair(it->first, it->second));
			}
		}

		if (result.empty())
		{
			throw EmployeeNotFoundException();
		}

		system("cls");
		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
		cout << "|  Ид  |       Имя       |      Фамилия     |     Телефон     |       Должность       |" << endl;
		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;

		for (auto it = result.begin(); it != result.end(); it++)
		{
			cout << "|" << setw(6) << left << it->first;
			cout << "|" << setw(17) << left << it->second.getFirstname();
			cout << "|" << setw(18) << left << it->second.getSurname();
			cout << "|" << setw(17) << left << it->second.getTelephone();
			cout << "|" << setw(23) << left << it->second.getPosition() << "|" << endl;
		}

		cout << "+------+-----------------+------------------+-----------------+-----------------------+" << endl;
	}
	catch (EmptyEmployeesListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (EmployeeNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void Bank::sortEmployees()
{
	try
	{
		if (employees_.empty())
		{
			throw EmptyEmployeesListException();
		}

		vector<Employee> employees_copy;

		for (auto it = employees_.begin(); it != employees_.end(); it++)
		{
			employees_copy.push_back(it->second);
		}

		sort(employees_copy.begin(), employees_copy.end(), [](const Employee& first, const Employee& second) -> bool
		{
			return first.getSurname() < second.getSurname();
		});

		employees_.clear();

		for (auto it = employees_copy.begin(); it != employees_copy.end(); it++)
		{
			employees_.insert(make_pair(employees_.empty() ? 1 : employees_.size() + 1, *it));
		}

		writeInTxt();

		cout << "Сотрудники успешно отсортированы!" << endl;
	}
	catch (EmptyEmployeesListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void Bank::editFirstname()
{
	try
	{
		showEditableEmployee();

		string firstname;
		cout << "Введите новое имя сотрудника: ";
		cin.ignore();
		getline(cin, firstname);

		if (!regex_match(firstname, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		editableEmployee_.second->setFirstname(firstname);
		writeInTxt();

		system("cls");
		showEditableEmployee();
		cout << "Имя сотрудника успешно изменено!" << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableEmployee();
		cout << ex.what() << endl;
	}
}

void Bank::editSurname()
{
	try
	{
		showEditableEmployee();

		string surname;
		cout << "Введите новую фамилию сотрудника: ";
		cin.ignore();
		getline(cin, surname);

		if (!regex_match(surname, regex("^[a-zA-Zа-яА-Я -]+$")))
		{
			throw InvalidInputException();
		}

		editableEmployee_.second->setSurname(surname);
		writeInTxt();

		system("cls");
		showEditableEmployee();
		cout << "Фамилия сотрудника успешно изменена!" << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableEmployee();
		cout << ex.what() << endl;
	}
}

void Bank::editTelephone()
{
	try
	{
		showEditableEmployee();

		string telephone;
		cout << "Введите новый телефон сотрудника: ";
		cin.ignore();
		getline(cin, telephone);

		if (!regex_match(telephone, regex("^((\\+375)+([0-9]){9})$")))
		{
			throw InvalidInputException();
		}

		editableEmployee_.second->setTelephone(telephone);
		writeInTxt();

		system("cls");
		showEditableEmployee();
		cout << "Телефон сотрудника успешно изменен!" << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableEmployee();
		cout << ex.what() << endl;
	}
}

void Bank::editPosition()
{
	try
	{
		showEditableEmployee();

		string position;
		cout << "Введите новую должность сотрудника: ";
		cin.ignore();
		getline(cin, position);

		if (!regex_match(position, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		editableEmployee_.second->setPosition(position);
		writeInTxt();

		system("cls");
		showEditableEmployee();
		cout << "Должность сотрудника успешно изменена!" << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableEmployee();
		cout << ex.what() << endl;
	}
}

Bank::~Bank() = default;
