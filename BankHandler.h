#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

#include "Functions.h"
#include "Bank.h"

#include "BankNotFoundException.h"
#include "BankAlreadyExistsException.h"
#include "EmptyBankListException.h"

using namespace std;

class Bank;

class BankHandler
{
	static map<unsigned, Bank> banks_;
	static Bank* currentBank_;
	static Bank* editableBank_;

	static string filename;

	static void editBankTitle();
	static void editBankCity();

	static void writeInTxt();
	static void readFromTxt();
public:
	BankHandler();
	explicit BankHandler(const map<unsigned, Bank> banks);

	static void setBanks(const map<unsigned, Bank>& banks);
	
	static map<unsigned, Bank> getBanks();

	static unsigned getBankId(Bank* bank);

	static void chooseBank();
	static void addBank();
	static void deleteBank();
	static void editBank();
	static void findBank();
	static void sortBanks();
	static void showBanks();
	static void showEditableBank();

	~BankHandler();
};

