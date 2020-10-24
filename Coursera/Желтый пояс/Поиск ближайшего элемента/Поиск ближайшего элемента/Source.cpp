#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
	const set<int>& numbers,
	int border)
{
	set<int>::const_iterator it = numbers.lower_bound(border);
	if (numbers.size() == 0)
	{
		return it;
	}

	if (it == numbers.end())
	{
		it = prev(it);
		return it;
	}

	if (it == numbers.begin())
	{
		return it;
	}

	if ((abs(border - *prev(it)) <= abs(border - *it)) && (*prev(it) < *it) && (*it != border))
	{
		it = prev(it);
	}
	return it;
}

int main()
{
	set<int> numbers = { 1, 4, 6 };
	cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

	return 0;
}