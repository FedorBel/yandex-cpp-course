#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <tuple>
#include <utility>

bool operator<(const Region& lhs, const Region& rhs)
{
	return tie(lhs.names, lhs.parent_std_name, lhs.population, lhs.std_name) <
		tie(rhs.names, rhs.parent_std_name, rhs.population, rhs.std_name);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	int result = 0;
	map<Region, int> repetition_count;
	for (const Region& region : regions) {
		result = max(result, ++repetition_count[region]);
	}
	return result;
}