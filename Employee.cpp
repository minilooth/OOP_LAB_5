#include "Employee.h"

Employee::Employee() = default;

Employee::Employee(const string & firstname, const string & surname, const string& telephone, const string & position)
{
	firstname_ = firstname;
	surname_ = surname;
	telephone_ = telephone;
	position_ = position;
}

void Employee::setFirstname(const string& firstname)
{
	firstname_ = firstname;
}

void Employee::setSurname(const string& surname)
{
	surname_ = surname;
}

void Employee::setTelephone(const string& telephone)
{
	telephone_ = telephone;
}

void Employee::setPosition(const string& position)
{
	position_ = position;
}

string Employee::getFirstname() const
{
	return firstname_;
}

string Employee::getSurname() const
{
	return surname_;
}

string Employee::getTelephone() const
{
	return telephone_;
}

string Employee::getPosition() const
{
	return position_;
}

Employee::~Employee() = default;
