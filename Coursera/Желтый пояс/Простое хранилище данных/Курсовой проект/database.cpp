#include "database.h"

map<Date, vector<string>>::const_iterator FindNearestElement(const map<Date, vector<string>>& numbers,
	const Date& border) {
	// Запрашиваем итератор на первый элемент, не меньший border;
	// если такого элемента нет, то мы получим numbers.end()
	// set::lower_bound ->
	// http://ru.cppreference.com/w/cpp/container/set/lower_bound
	const auto first_not_less = numbers.lower_bound(border);

	// Если множество пусто или до первого элемента не меньше border
	// нет элементов, то мы уже получили ответ
	if (first_not_less == numbers.begin()) {
		return first_not_less;
	}
	if (first_not_less->first == border)
	{
		return first_not_less;
	}

	// Если элементов, не меньших border, нет и set не пуст, то достаточно взять
	// итератор на последний элемент, меньший border
	// prev -> http://ru.cppreference.com/w/cpp/iterator/prev
	/*const auto last_less = prev(first_not_less);
	if (first_not_less == numbers.end()) {
		return last_less;
	}	

	// Разыменуем оба итератора-кандидата и выберем тот,
	// чей элемент ближе к искомому
	const bool is_left = (border - last_less->first <= first_not_less->first - border);
	return is_left ? last_less : first_not_less;*/
	return prev(first_not_less);
}

void Database::Add(const Date & date, const string & event)
{	
	try
	{
		if (storage.at(date).find(event) == storage.at(date).end())
		{
			prior_storage[date].push_back(event);
		}
	}
	catch (const std::exception&)
	{
		prior_storage[date].push_back(event);
	}
	
	storage[date].insert(event);
}

void Database::Print(ostream & os) const
{
	for (const auto& item : prior_storage) {
		for (const string& event : item.second) {
			os << item.first << " " << event << endl;
		}
	}
}

string Database::Last(const Date & date) const
{
	auto it = FindNearestElement(prior_storage, date);
	
	if (it != prior_storage.end())
	{
		if (it->first <= date)
		{
			return it->first.Date_to_string() + " " + prior_storage.at(it->first).back();
		}		
	}
	throw invalid_argument("No entries");
}
