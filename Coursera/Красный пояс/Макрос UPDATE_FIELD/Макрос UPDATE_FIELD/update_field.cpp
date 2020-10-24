#include "airline_ticket.h"
#include <iostream>
#include <tuple>

using namespace std;

istream& operator>>(istream& is, Date& d)
{
	is >> d.year;
	is.ignore(1);
	is >> d.month;
	is.ignore(1);
	is >> d.day;
	return is;
}

istream& operator>>(istream& is, Time& d)
{
	is >> d.hours;
	is.ignore(1);
	is >> d.minutes;
	return is;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.year, lhs.month, lhs.day) == make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Time& lhs, const Time& rhs)
{
	return make_tuple(lhs.hours, lhs.minutes) == make_tuple(rhs.hours, rhs.minutes);
}

ostream& operator << (ostream& os, const Date& s) {
	os << "{" << s.year << " " << s.month << " " << s.day << "}";
	bool first = true;

	return os;
}

ostream& operator << (ostream& os, const Time& s) {
	os << "{" << s.hours << " " << s.minutes << "}";
	bool first = true;

	return os;
}

#define UPDATE_FIELD(ticket, field, values)  {\
auto it = values.find(#field);\
if (it != values.end()) {\
	istringstream is(it->second);\
	is >> ticket.field;\
}}