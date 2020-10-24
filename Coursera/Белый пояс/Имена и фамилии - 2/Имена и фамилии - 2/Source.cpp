#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

// ���� ��� ����������, ���������� ������ ������
string FindNameByYear(const map<int, string>& names, int year) 
{
	string name;  // ���������� ��� ����������

	// ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
	for (const auto& item : names) 
	{
		// ���� ��������� ��� �� ������ �������, ��������� ���
		if (item.first <= year) 
		{
			name = item.second;
		}
		else 
		{
			// ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
			break;
		}
	}

	return name;
}

class Person 
{
public:
	void ChangeFirstName(int year, const string& first_name) 
	{
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) 
	{
		last_names[year] = last_name;
	}
	string GetFullName(int year) {
		// �������� ��� � ������� �� ��������� �� ��� year
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		// ���� � ���, � ������� ����������
		if (first_name.empty() && last_name.empty()) 
		{
			return "Incognito";

			// ���� ���������� ������ ���
		}
		else if (first_name.empty()) 
		{
			return last_name + " with unknown first name";

			// ���� ���������� ������ �������
		}
		else if (last_name.empty()) 
		{
			return first_name + " with unknown last name";

			// ���� �������� � ���, � �������
		}
		else 
		{
			return first_name + " " + last_name;
		}
	}
	string GetFullNameWithHistory(int year) {
		string first_name = FindNameByYear(first_names, year);
		string last_name = FindNameByYear(last_names, year);
		if (first_name.empty() && last_name.empty())
		{
			return "Incognito";

			// ���� ���������� ������ ���
		}
		
		if (!first_name.empty())
		{
			first_name += " (";
			for (auto i = year-1; i < first_names.begin()->first; i--)
			{
				const string first_name_history = FindNameByYear(first_names, year);
				const string tmp = FindNameByYear(first_names, year + 1);
				if (first_name.empty() && tmp == first_name_history)
				{
					continue;

					// ���� ���������� ������ ���
				}
				else
				{
					first_name += first_name_history + ", ";
				}
			}
			first_name[first_name.size() - 1] = ')';
		}
		
		if (!last_name.empty())
		{
			last_name += " (";
			for (int i = year - 1; i < first_names.begin()->first; i--)
			{
				const string last_name_history = FindNameByYear(last_names, year);
				const string tmp = FindNameByYear(last_names, year + 1);
				if (last_name.empty() && tmp == last_name_history)
				{
					continue;

					// ���� ���������� ������ ���
				}
				else
				{
					last_name += last_name_history + ", ";
				}
			}
			last_name[last_name.size() - 1] = ')';
		}

		if (first_name.empty())
		{
			return last_name + " with unknown first name";

			// ���� ���������� ������ �������
		}
		else if (last_name.empty())
		{
			return first_name + " with unknown last name";

			// ���� �������� � ���, � �������
		}
		else
		{
			return first_name + " " + last_name;
		}

	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
};

int main()
{
	Person person;

	person.ChangeFirstName(1900, "Eugene");
	person.ChangeLastName(1900, "Sokolov");
	person.ChangeLastName(1910, "Sokolov");
	person.ChangeFirstName(1920, "Evgeny");
	person.ChangeLastName(1930, "Sokolov");
	cout << person.GetFullNameWithHistory(1940) << endl;

	return 0;
}