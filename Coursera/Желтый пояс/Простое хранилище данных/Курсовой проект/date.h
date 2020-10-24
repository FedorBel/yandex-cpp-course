#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

class Date {
public:
	//Date();	
	// конструктор выбрасывает исключение, если его аргументы некорректны
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string Date_to_string() const;

private:
	int year;
	int month;
	int day;
};

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs);

Date ParseDate(istream& date);

ostream& operator<<(ostream& os, const Date& date);

bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date operator-(const Date& lhs, const Date& rhs);
