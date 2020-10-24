#include "airline_ticket.h"
#include <tuple>
#include <iostream>

bool operator<(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.year, lhs.month, lhs.day) < make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return make_tuple(lhs.year, lhs.month, lhs.day) == make_tuple(rhs.year, rhs.month, rhs.day);
}

ostream& operator << (ostream& os, const Date& s) {
	os << "{" << s.year << " " << s.month << " " << s.day << "}";
	bool first = true;

	return os;
}

bool operator<(const Time& lhs, const Time& rhs)
{
	return make_tuple(lhs.hours, lhs.minutes) < make_tuple(rhs.hours, rhs.minutes);
}

#define SORT_BY(field) [](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
return lhs.field < rhs.field; }