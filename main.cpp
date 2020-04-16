#include <iostream>

#include "Functions.h"

#include "BankHandler.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BankHandler* bankHandler = new BankHandler();

	while (true)
	{
		switch (mainMenu())
		{
		case MainMenuAction::CHOOSE_BANK :
			system("cls");
			BankHandler::chooseBank();
			break;
		case MainMenuAction::ADD_BANK :
			system("cls");
			BankHandler::addBank();
			system("pause");
			break;
		case MainMenuAction::DELETE_BANK :
			system("cls");
			BankHandler::deleteBank();
			system("pause");
			break;
		case MainMenuAction::EDIT_BANK :
			system("cls");
			BankHandler::editBank();
			break;
		case MainMenuAction::SHOW_BANKS :
			system("cls");
			BankHandler::showBanks();
			system("pause");
			break;
		case MainMenuAction::SORT_BANKS :
			system("cls");
			BankHandler::sortBanks();
			system("pause");
			break;
		case MainMenuAction::FIND_BANK :
			system("cls");
			BankHandler::findBank();
			system("pause");
			break;
		case MainMenuAction::QUIT :
			delete bankHandler;
			return 0;
		default:
			break;
		}
	}
}

