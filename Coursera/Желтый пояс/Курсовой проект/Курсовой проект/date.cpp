#include "date.h"

Date::Date(int new_year, int new_month, int new_day) {
	year = new_year;
	/*if (new_month > 12 || new_month < 1) {
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}*/
	month = new_month;
	/*if (new_day > 31 || new_day < 1) {
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}*/
	day = new_day;
}

int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}

string Date::Date_to_string() const
{
	ostringstream os;
	os << setw(4) << setfill('0') << GetYear() <<
		"-" << setw(2) << setfill('0') << GetMonth() <<
		"-" << setw(2) << setfill('0') << GetDay();
	return os.str();
}

bool operator<(const Date & lhs, const Date & rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

Date ParseDate(istream& date_stream)
{		
	int year;
	date_stream >> year;
	date_stream.ignore(1);

	int month;
	date_stream >> month;
	date_stream.ignore(1);

	int day;
	date_stream >> day;	
		
	return Date(year, month, day);
}

ostream & operator<<(ostream & os, const Date & date)
{
	os << setw(4) << setfill('0') << date.GetYear() <<
		"-" << setw(2) << setfill('0') << date.GetMonth() <<
		"-" << setw(2) << setfill('0') << date.GetDay();
	return os;
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator==(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}
bool operator>(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) > make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator>=(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

Date operator-(const Date & lhs, const Date & rhs)
{
	return Date(lhs.GetYear()-rhs.GetYear(), lhs.GetMonth()-rhs.GetMonth(), lhs.GetDay()-rhs.GetDay());
}

