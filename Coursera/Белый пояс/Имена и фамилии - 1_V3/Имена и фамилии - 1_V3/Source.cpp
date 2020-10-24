#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Person
{
public:
	void ChangeFirstName(int year, const string& first_name)
	{
		if (name_year.find(year) == name_year.end()) // Если нет в словаре
		{
			name_year[year].first_name = first_name;
			name_year[year].is_changed_fir_name = 1;
			ChangeFirstName_Con(year, first_name);
		}
		else
		{
			if (!(name_year.find(year)->second.is_changed_fir_name)) // Если имя еще не изменяли
			{
				name_year[year].first_name = first_name;
				name_year[year].is_changed_fir_name = 1;
				ChangeFirstName_Con(year, first_name);
			}
		}
	}
	void ChangeLastName(int year, const string& last_name)
	{
		if (name_year.find(year) == name_year.end()) // Если нет в словаре
		{
			name_year[year].last_name = last_name;
			name_year[year].is_changed_las_name = 1;
			ChangeLastName_Con(year, last_name);
		}
		else
		{
			if (!(name_year.find(year)->second.is_changed_las_name)) // Если фамилию еще не изменяли
			{
				name_year[year].last_name = last_name;
				name_year[year].is_changed_las_name = 1;
				ChangeLastName_Con(year, last_name);
			}
		}
	}
	string GetFullName(int year)
	{
		if (name_year.size() == 0)
		{
			return "Incognito";
		}

		if (name_year.find(year) == name_year.end()) // Если года нет в словаре
		{
			if (year < name_year.begin()->first)
			{
				return "Incognito";
			}

			while (name_year.find(year) == name_year.end())  // Найти ближайший минимальный год
			{
				year--;
			}

			if (no_first_name_b(year)) // Нет имени
			{
				return no_first_name(year);
			}
			else if (no_last_name_b(year)) // Нет фамилии
			{
				return no_last_name(year);
			}
			else
			{
				return name_year.find(year)->second.first_name + " " + name_year.find(year)->second.last_name;
			}

		}

		// Есть в словаре

		else if (no_first_name_b(year)) // Нет имени
		{
			return no_first_name(year);
		}
		else if (no_last_name_b(year)) // Нет фамилии
		{
			return no_last_name(year);
		}
		else
		{
			return name_year[year].first_name + " " + name_year[year].last_name;
		}

	}
private:

	void ChangeFirstName_Con(int year, const string& first_name)
	{
		if (!(name_year.find(year)->second.is_changed_las_name))
		{
			auto it = --name_year.find(year);
			if (it != name_year.end())
			{
				name_year[year].last_name = it->second.last_name;
			}
		}

		for (auto i = ++name_year.find(year); i != name_year.end(); ++i)
		{
			if (i->second.first_name == "unknown" || !(i->second.is_changed_fir_name))
			{
				i->second.first_name = first_name;
			}

			if (i->second.is_changed_fir_name)
			{
				break;
			}
		}
	}

	void ChangeLastName_Con(int year, const string& last_name)
	{
		if (!(name_year.find(year)->second.is_changed_fir_name))
		{
			auto it = --name_year.find(year);
			if (it != name_year.end())
			{
				name_year[year].first_name = it->second.first_name;
			}
		}

		for (auto i = ++name_year.find(year); i != name_year.end(); ++i)
		{
			if (i->second.last_name == "unknown" || !(i->second.is_changed_las_name))
			{
				i->second.last_name = last_name;
			}

			if (i->second.is_changed_las_name)
			{
				break;
			}
		}
	}

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