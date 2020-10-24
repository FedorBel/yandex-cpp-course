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
	// ����������� ����������� ����������, ���� ��� ��������� �����������
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

// ���������� ��������� ��� ��� ���������� ��� ������������� �� � �������� ������ �������
bool operator<(const Date& lhs, const Date& rhs);

Date ParseDate(istream& date);

ostream& operator<<(ostream& os, const Date& date);

bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date operator-(const Date& lhs, const Date& rhs);
