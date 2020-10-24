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
		if (name_year.find(year) == name_year.end())
		{
			name_year[year].first_name = first_name;
			name_year[year].is_changed_fir_name = 1;
		}
		else
		{

		}

		auto it = --name_year.find(year);
		if (it!=name_year.end())
		{
			name_year[year].last_name = it->second.last_name;
		}
		
		for (auto i = ++name_year.find(year); i != name_year.end(); ++i)
		{
			if (i->second.first_name == "unknown")
			{
				i->second.first_name = first_name;
			}
		}

		if (++name_year.find(year) != name_year.end())
		{
			bool tmp = (++name_year.find(year))->second.is_changed_fir_name;
			if (!tmp)
			{
				(++name_year.find(year))->second.first_name = first_name;
			}
		}
	}
	void ChangeLastName(int year, const string& last_name)
	{
		name_year[year].last_name = last_name;
		name_year[year].is_changed_las_name = 1;
		auto it = --name_year.find(year);
		if (it != name_year.end())
		{
			name_year[year].first_name = it->second.first_name;
		}

		for (auto i = ++name_year.find(year); i != name_year.end(); ++i)
		{
			if (i->second.last_name == "unknown")
			{
				i->second.last_name = last_name;
			}
		}

		if (++name_year.find(year) != name_year.end())
		{
			bool tmp = (++name_year.find(year))->second.is_changed_las_name;
			if (!tmp)
			{
				(++name_year.find(year))->second.last_name = last_name;
			}
		}
	}
	string GetFullName(int year)
	{
		if (name_year.find(year) == name_year.end())
		{
			if (year<name_year.begin()->first)
			{
				return "Incognito";
			}

			while (name_year.find(year)== name_year.end())
			{
				year--;
			}
			auto it = name_year.find(year);
			if (no_first_name_b(year))
			{
				return no_first_name(year);
			}
			else if (no_last_name_b(year))
			{
				return no_last_name(year);
			}
			else
			{
				return it->second.first_name + " " + it->second.last_name;
			}	

		}
		else if (no_first_name_b(year))
		{
			return no_first_name(year);
		}
		else if (no_last_name_b(year))
		{
			return no_last_name(year);
		}
		else
		{
			return name_year[year].first_name + " " + name_year[year].last_name;
		}
		
	}
private:
	bool no_first_name_b(int year)
	{
		return (name_year.find(year)->second.first_name == "unknown");
	}
	string no_first_name(int year)
	{
		return name_year[year].last_name + " with unknown first name";
	}
	bool no_last_name_b(int year)
	{
		return (name_year.find(year)->second.last_name == "unknown");
	}
	string no_last_name(int year)
	{
		return name_year[year].first_name + " with unknown last name";
	}
	typedef struct Full_name
	{
		string first_name = "unknown";
		string last_name = "unknown";
		bool is_changed_fir_name = 0;
		bool is_changed_las_name = 0;
	};
	
	map<int, Full_name> name_year;  // Изменение имени или фамилии
};

int main()
{
	Person person;

	person.ChangeLastName(1965, "Last");
	person.ChangeFirstName(1964, "First_1964_1");
	person.ChangeFirstName(1967, "First_1967");
	person.ChangeFirstName(1964, "First_1964_2");

	cout << person.GetFullName(1963) << endl;
	cout << person.GetFullName(1964) << endl;
	cout << person.GetFullName(1965) << endl;
	cout << person.GetFullName(1967) << endl;

	return 0;
}