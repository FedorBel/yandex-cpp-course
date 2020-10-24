#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m);

int main()
{
	set<string> values = BuildMapValuesSet({
	{1, "odd"},
	{2, "even"},
	{3, "odd"},
	{4, "even"},
	{5, "odd"}
		});

	for (const string& value : values) {
		cout << value << endl;
	}

	return 0;
}

set<string> BuildMapValuesSet(const map<int, string>& m)
{
	set<string> mySet;
	for (const auto& it : m)
	{
		mySet.insert(it.second);
	}


	return mySet;
}
