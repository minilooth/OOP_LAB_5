#pragma once

#include <string>

using namespace std;

class Employee
{
	string firstname_;
	string surname_;
	string telephone_;
	string position_;
public:
	Employee();
	Employee(const string& firstname, const string& surname, const string& telephone, const string& position);

	void setFirstname(const string& firstname);
	void setSurname(const string& surname);
	void setTelephone(const string& telephone);
	void setPosition(const string& position);

	string getFirstname() const;
	string getSurname() const;
	string getTelephone() const;
	string getPosition() const;

	~Employee();
};

