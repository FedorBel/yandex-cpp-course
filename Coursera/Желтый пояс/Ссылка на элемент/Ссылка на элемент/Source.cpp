#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

template<typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& m, const Key& key);

int main()
{
	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue

	return 0;
}

template<typename Key, typename Value>
Value & GetRefStrict(map<Key, Value>& m, const Key & key)
{
	if (m.find(key) == m.end())
	{
		throw runtime_error("");
	}

	return m[key];
}
