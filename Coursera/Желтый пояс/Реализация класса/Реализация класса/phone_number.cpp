#include "phone_number.h"

#include <sstream>

PhoneNumber::PhoneNumber(const string & international_number)
{
	stringstream ss(international_number);

	bool ok = true;
		
	ok = ok && (ss.peek() == '+');
	ss.ignore(1);		

	ok = ok && getline(ss, country_code_, '-');
	ok = ok && getline(ss, city_code_, '-');	
	ok = ok && (ss >> local_number_);

	if (!ok) {
		throw invalid_argument("Wrong number format.");
	}
}

string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
