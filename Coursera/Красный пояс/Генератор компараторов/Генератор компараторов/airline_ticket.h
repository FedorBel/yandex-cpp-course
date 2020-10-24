#pragma once

#include <string>
#include <tuple>
using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

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
