#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

#include "phone_number.h"

using namespace std;

int main()
{
	try
	{
		PhoneNumber number("+7-495-111-22-33");
		string my_number = number.GetInternationalNumber();

		PhoneNumber number1("+7-495-1112233");
		string my_number1 = number1.GetInternationalNumber();

		PhoneNumber number2("+323-22-460002");
		string my_number2 = number2.GetInternationalNumber();

		PhoneNumber number3("+1-2-coursera-cpp");
		string my_number3 = number3.GetInternationalNumber();

		PhoneNumber number4("1-2-333");
		string my_number4 = number4.GetInternationalNumber();

		PhoneNumber number5("+7-1233");
		string my_number5 = number5.GetInternationalNumber();
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	
	return 0;
}