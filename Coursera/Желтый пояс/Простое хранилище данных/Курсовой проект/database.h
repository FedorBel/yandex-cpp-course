#pragma once

#include "date.h"

#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

map<Date, vector<string>>::const_iterator FindNearestElement(const map<Date, vector<string>>& numbers,
	const Date& border);

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	template <class Func> int RemoveIf(Func func);
	template <class Func> vector<string> FindIf(Func func) const;
	string Last(const Date& date) const;
private:
	map<Date, set<string>> storage;
	map<Date, vector<string>> prior_storage;
};

template<class Func>
inline int Database::RemoveIf(Func func)
{		
	int deleted = 0;

	/*for (auto date = prior_storage.begin(); date != prior_storage.end();)
	{		
		for (auto event = date->second.begin(); event != date->second.end(); event++)
		{
			auto it = stable_partition(date->second.begin(), date->second.end(), func(date->first, *event));
			if (storage[date->first].find(*event) != storage[date->first].end())
			{
				storage[date->first].erase(*event);
				deleted++;				
			}
			prior_storage[date->first].erase(date->second.begin(), it);
		}
		
		if (storage[date->first].empty())
		{
			storage.erase(date->first);
			date = prior_storage.erase(date);
		}
		else
		{
			++date;
		}
	}*/

	for (auto date = prior_storage.begin(); date != prior_storage.end();)
	{		
		vector<string> to_delete;
		for (auto event = date->second.begin(); event != date->second.end(); ++event)
		{			
			if (func(date->first, *event))
			{
				to_delete.push_back(*event);
				storage[date->first].erase(*event);
				deleted++;
			}		
		}

		if (!to_delete.empty())
		{
			auto it = remove_if(date->second.begin(), date->second.end(),
				[to_delete](const string& str) {
				for (const auto& del : to_delete) {
					if (str == del) {
						return true;
					}
				} return false;
			});
			prior_storage[date->first].erase(it, date->second.end());					   
		}
		

		if (storage[date->first].empty())
		{
			storage.erase(date->first);
			date = prior_storage.erase(date);
		}
		else
		{
			++date;
		}
	}

	return deleted;
}

template<class Func>
inline vector<string> Database::FindIf(Func func) const
{
	vector<string> found;	

	for (auto date = prior_storage.begin(); date != prior_storage.end(); ++date)
	{
		for (auto event = date->second.begin(); event != date->second.end(); ++event)
		{
			if (func(date->first, *event))
			{
				found.push_back(date->first.Date_to_string() + " " + *event);
			}
		}		
	}

	return found;
}
