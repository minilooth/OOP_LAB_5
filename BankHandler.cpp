#include "BankHandler.h"

map<unsigned, Bank> BankHandler::banks_;
Bank* BankHandler::currentBank_ = nullptr;
Bank* BankHandler::editableBank_ = nullptr;
string BankHandler::filename = "Data/banks.txt";

BankHandler::BankHandler()
{
	currentBank_ = nullptr;
	editableBank_ = nullptr;
	readFromTxt();
}

BankHandler::BankHandler(const map<unsigned, Bank> banks)
{
	banks_ = banks;
	currentBank_ = nullptr;
}

void BankHandler::setBanks(const map<unsigned, Bank>& banks)
{
	banks_ = banks;
}

map<unsigned, Bank> BankHandler::getBanks()
{
	return banks_;
}

unsigned BankHandler::getBankId(Bank* bank)
{
	for (auto it = banks_.begin(); it != banks_.end(); it++)
	{
		if (&it->second == bank)
		{
			return it->first;
		}
	}
	return 0;
}

void BankHandler::writeInTxt()
{
	ofstream banksData;
	banksData.open(filename, ios::trunc);

	if (banksData.is_open())
	{
		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			banksData << it->second.getTitle() << ";"
				<< it->second.getCity().getTitle() << endl;
			it->second.writeInTxt();
		}
		banksData.close();
	}
}

void BankHandler::readFromTxt()
{
	string token;

	string title;
	string city;

	ifstream banksData;
	banksData.open("Data/Banks/banks.txt");

	if (banksData.is_open())
	{
		while (!banksData.eof())
		{
			if (getline(banksData, token, '\n'))
			{
				auto data = string_splitter(token, ';');

				title = data.at(0);
				city = data.at(1);

				banks_.insert(make_pair(banks_.empty() ? 1 : banks_.size() + 1, Bank(title, City(city))));
			}
		}
		banksData.close();
	}
}

void BankHandler::chooseBank()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		showBanks();

		string id;
		cout << "Введите ид банка: ";
		cin >> id;

		if (!regex_match(id, regex("^[0-9]+$")))
		{
			throw InvalidInputException();
		}

		if (banks_.find(stoul(id)) == banks_.end())
		{
			throw BankNotFoundException();
		}

		currentBank_ = &banks_.at(stoul(id));

		while (true)
		{
			switch (bankMenu())
			{
			case BankMenuAction::ADD_EMPLOYEE:
				system("cls");
				currentBank_->addEmployee();
				system("pause");
				break;
			case BankMenuAction::DELETE_EMPLOYEE:
				system("cls");
				currentBank_->deleteEmployee();
				system("pause");
				break;
			case BankMenuAction::EDIT_EMPLOYEE:
				system("cls");
				currentBank_->editEmployee();
				break;
			case BankMenuAction::SHOW_EMPLOYEES:
				system("cls");
				currentBank_->showEmployees();
				system("pause");
				break;
			case BankMenuAction::SORT_EMPLOYEES :
				system("cls");
				currentBank_->sortEmployees();
				system("pause");
			case BankMenuAction::FIND_EMPLOYEE:
				system("cls");
				currentBank_->findEmployee();
				system("pause");
				break;
			case BankMenuAction::BACK_TO_MAIN_MENU:
				currentBank_ = nullptr;
				return;
			default:
				break;
			}
		}
	}
	catch (BankNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
		system("pause");
	}
	catch (EmptyBankListException & ex)
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
}

void BankHandler::addBank()
{
	try
	{
		string title;
		cout << "Введите наименование банка: ";
		cin.ignore();
		getline(cin, title);

		if (!regex_match(title, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		string city;
		cout << "Введите название города: ";
		getline(cin, city);

		if (!regex_match(city, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			if (it->second.getTitle() == title && it->second.getCity().getTitle() == city)
			{
				throw BankAlreadyExistsException();
			}
		}

		banks_.insert(make_pair(banks_.empty() ? 1 : banks_.size() + 1, Bank(title, City(city))));
		writeInTxt();

		cout << endl << "Банк успешно добавлен!" << endl << endl;
	}
	catch (BankAlreadyExistsException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void BankHandler::deleteBank()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		showBanks();

		string id;
		cout << "Введите ид банка для удаления: ";
		cin >> id;

		if (!regex_match(id, regex("^[0-9]+$")))
		{
			throw InvalidInputException();
		}

		if (banks_.find(stoul(id)) == banks_.end())
		{
			throw BankNotFoundException();
		}

		remove(("Data/Employees/" + banks_.find(stoul(id))->second.getTitle() + "_" + banks_.find(stoul(id))->second.getCity().getTitle() + ".txt").c_str());
		banks_.erase(stoul(id));
		writeInTxt();

		cout << endl << "Банк успешно удален!" << endl << endl;
	}
	catch (EmptyBankListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (BankNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void BankHandler::editBank()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		showBanks();

		string id;
		cout << "Введите ид банка для редактирования: ";
		cin >> id;

		if (!regex_match(id, regex("^[0-9]+$")))
		{
			throw InvalidInputException();
		}

		auto it = banks_.find(stoul(id));

		if (it == banks_.end())
		{
			throw BankNotFoundException();
		}

		editableBank_ = &it->second;

		while (true)
		{
			switch (bankEditMenu())
			{
			case BankEditMenuAction::EDIT_TITLE :
				system("cls");
				editBankTitle();
				system("pause");
				break;
			case BankEditMenuAction::EDIT_CITY :
				system("cls");
				editBankCity();
				system("pause");
				break;
			case BankEditMenuAction::BACK_TO_MAIN_MENU :
				editableBank_ = nullptr;
				return;
			default:
				break;
			}
		}
	}
	catch (EmptyBankListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
		system("pause");
	}
	catch (BankNotFoundException & ex)
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
}

void BankHandler::findBank()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		string title;
		cout << "Введите наименование банка для поиска: ";
		cin.ignore();
		getline(cin, title);

		if (!regex_match(title, regex("^[A-Za-zА-Яа-я ]+$")))
		{
			throw InvalidInputException();
		}

		map<unsigned, Bank> result;

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			if (it->second.getTitle() == title)
			{
				result.insert(make_pair(it->first, it->second));
			}
		}

		if (result.empty())
		{
			throw BankNotFoundException();
		}

		system("cls");
		cout << "+------+------------------+---------------+" << endl;
		cout << "|  Ид  |Наименование банка|     Город     |" << endl;
		cout << "+------+------------------+---------------+" << endl;

		for (auto it = result.begin(); it != result.end(); it++)
		{
			cout << "|" << setw(6) << left << it->first;
			cout << "|" << setw(18) << left << it->second.getTitle();
			cout << "|" << setw(15) << left << it->second.getCity().getTitle() << "|" << endl;
		}

		cout << "+------+------------------+---------------+" << endl;
	}
	catch (EmptyBankListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (BankNotFoundException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void BankHandler::sortBanks()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		vector<Bank> banks_copy;

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			banks_copy.push_back(it->second);
		}

		sort(banks_copy.begin(), banks_copy.end(), [](const Bank& a, const Bank& b) -> bool
		{
			return a.getTitle() < b.getTitle();
		});

		banks_.clear();

		for (auto it = banks_copy.begin(); it != banks_copy.end(); it++)
		{
			banks_.insert(make_pair(banks_.empty() ? 1 : banks_.size() + 1, *it));
		}

		writeInTxt();

		cout << "Банки успешно отсортированы!" << endl;
	}
	catch (EmptyBankListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void BankHandler::showBanks()
{
	try
	{
		if (banks_.empty())
		{
			throw EmptyBankListException();
		}

		cout << "+------+------------------+---------------+" << endl;
		cout << "|  Ид  |Наименование банка|     Город     |" << endl;
		cout << "+------+------------------+---------------+" << endl;

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			cout << "|" << setw(6) << left << it->first;
			cout << "|" << setw(18) << left << it->second.getTitle();
			cout << "|" << setw(15) << left << it->second.getCity().getTitle() << "|" << endl;
		}

		cout << "+------+------------------+---------------+" << endl;
	}
	catch (EmptyBankListException & ex)
	{
		system("cls");
		cout << ex.what() << endl;
	}
}

void BankHandler::showEditableBank()
{
	cout << "+------+------------------+---------------+" << endl;
	cout << "|  Ид  |Наименование банка|     Город     |" << endl;
	cout << "+------+------------------+---------------+" << endl;

	cout << "|" << setw(6) << left << getBankId(editableBank_);
	cout << "|" << setw(18) << left << editableBank_->getTitle();
	cout << "|" << setw(15) << left << editableBank_->getCity().getTitle() << "|" << endl;

	cout << "+------+------------------+---------------+" << endl;
}

void BankHandler::editBankTitle()
{
	try
	{
		showEditableBank();

		string title;
		cout << "Введите новое наименование банка: ";
		cin.ignore();
		getline(cin, title);

		if (!regex_match(title, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			if (it->second.getTitle() == title && it->second.getCity().getTitle() == editableBank_->getCity().getTitle())
			{
				throw BankAlreadyExistsException();
			}
		}

		remove(("Data/Employees/" + editableBank_->getTitle() + "_" + editableBank_->getCity().getTitle() + ".txt").c_str());
		editableBank_->setTitle(title);
		writeInTxt();

		system("cls");
		showEditableBank();
		cout << "Наименование банка успешно изменено!" << endl;
	}
	catch (BankAlreadyExistsException & ex)
	{
		system("cls");
		showEditableBank();
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableBank();
		cout << ex.what() << endl;
	}
}

void BankHandler::editBankCity()
{
	try
	{
		showEditableBank();

		string city;
		cout << "Введите новый город банка: ";
		cin.ignore();
		getline(cin, city);

		if (!regex_match(city, regex("^[a-zA-Zа-яА-Я ]+$")))
		{
			throw InvalidInputException();
		}

		for (auto it = banks_.begin(); it != banks_.end(); it++)
		{
			if (it->second.getTitle() == editableBank_->getTitle() && it->second.getCity().getTitle() == city)
			{
				throw BankAlreadyExistsException();
			}
		}
		
		remove(("Data/Employees/" + editableBank_->getTitle() + "_" + editableBank_->getCity().getTitle() + ".txt").c_str());
		editableBank_->setCity(City(city));
		writeInTxt();

		system("cls");
		showEditableBank();
		cout << "Город банка успешно изменен!" << endl;
	}
	catch (BankAlreadyExistsException & ex)
	{
		system("cls");
		showEditableBank();
		cout << ex.what() << endl;
	}
	catch (InvalidInputException & ex)
	{
		system("cls");
		showEditableBank();
		cout << ex.what() << endl;
	}
}

BankHandler::~BankHandler()
{
	currentBank_ = nullptr;
	editableBank_ = nullptr;
}
