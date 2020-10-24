#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

int main()
{
	size_t n;
	cin >> n;

	list<size_t> people;
	map<size_t, list<size_t>::const_iterator> on_field;

	for (size_t i = 0; i < n; i++)
	{
		size_t current_num, insert_before_num;
		cin >> current_num >> insert_before_num;

		auto it = on_field.find(insert_before_num);
		if (it == on_field.end())
		{
			people.push_back(current_num);
			on_field[current_num] = prev(people.end());
		}
		else
		{
			people.insert(it->second, current_num);
			on_field[current_num] = prev(it->second);
		}
	}	

	for (const auto& el : people)
	{
		cout << el << endl;
	}

	return 0;
}