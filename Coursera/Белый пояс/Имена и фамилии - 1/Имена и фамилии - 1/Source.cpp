#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class Person 
{
public:
	void ChangeFirstName(int year, const string& first_name) 
	{
		name_year[year].first_name = first_name;
	}
	void ChangeLastName(int year, const string& last_name) 
	{
		name_year[year].last_name = last_name;
	}
	string GetFullName(int year) 
	{
		if (name_year.find(year)==name_year.end())
		{
			return "Incognito";
		}
		else if (name_year.find(year)->second.first_name == "unknown")
		{
			return name_year[year].last_name + " with unknown first name";
		}
		else if (name_year.find(year)->second.last_name == "unknown")
		{
			return name_year[year].first_name + " with unknown last name";
		}
		return name_year[year].first_name + " " + name_year[year].last_name;
	}
private:
	typedef struct Full_name
	{
		string first_name = "unknown";
		string last_name = "unknown";
	};
	map<int, Full_name> name_year;
};

int main()
{
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) 
	{
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) 
	{
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) 
	{
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}