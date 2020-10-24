#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year, int& tmp_year) {
	string name;  // изначально имя неизвестно

	// перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
	for (const auto& item : names) {
		// если очередной год не больше данного, обновляем имя
		if (item.first <= year) {
			name = item.second;
			tmp_year = item.first;
		}
		else {
			// иначе пора остановиться, так как эта запись и все последующие относятся к будущему
			break;
		}
	}

	return name;
}
string FindNameByYear_History(const map<int, string>& names, int year, string prev_name) {
	string name;  // изначально имя неизвестно
	int tmp_year = 0;
	string prev_name_tmp = prev_name + ", ";

	// перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
	for (const auto& item : names) {
		// если очередной год не больше данного, обновляем имя
		if (item.first < year) {
			name = item.second + ", ";
			tmp_year = item.first;
		}
		else {
			// иначе пора остановиться, так как эта запись и все последующие относятся к будущему
			break;
		}
	}
	year = tmp_year;
	if (name.size() != 0 && name != prev_name_tmp)
	{
		prev_name = name;
		return name + FindNameByYear_History(names, year, prev_name);
	}
	else if (name.size() != 0)
	{
		name.clear();
		return name + FindNameByYear_History(names, year, prev_name);
	}
	else
	{
		name.clear();
		return name;
	}
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		last_names[year] = last_name;
	}
	string GetFullName(int year) {
		// получаем имя и фамилию по состоянию на год year
		int tmp = 0;
		const string first_name = FindNameByYear(first_names, year, tmp);
		const string last_name = FindNameByYear(last_names, year, tmp);

		// если и имя, и фамилия неизвестны
		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

			// если неизвестно только имя
		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";

			// если неизвестна только фамилия
		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";

			// если известны и имя, и фамилия
		}
		else {
			return first_name + " " + last_name;
		}
	}
	string GetFullNameWithHistory(int year) 
	{
		int tmp_year = 0;
		string first_name = FindNameByYear(first_names, year, tmp_year);
		string first_name_history = FindNameByYear_History(first_names, year, first_name);
		if (first_name_history.size() != 0)
		{
			first_name_history.resize(first_name_history.size() - 1); // Убираем лишний пробел
			first_name_history = " (" + first_name_history;
			first_name_history[first_name_history.size() - 1] = ')';
			first_name += first_name_history;
		}

		string last_name = FindNameByYear(last_names, year, tmp_year);
		string last_name_history = FindNameByYear_History(last_names, year, last_name);
		if (last_name_history.size() != 0)
		{
			last_name_history.resize(last_name_history.size() - 1); // Убираем лишний пробел
			last_name_history = " (" + last_name_history;
			last_name_history[last_name_history.size() - 1] = ')';
			last_name += last_name_history;
		}

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

			// если неизвестно только имя
		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";

			// если неизвестна только фамилия
		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";

			// если известны и имя, и фамилия
		}
		else {
			return first_name + " " + last_name;
		}
	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	return 0;
}