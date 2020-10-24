#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <set>

#include "profile.h"

using namespace std;

class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}
	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}
		const set<int>& reachable_stations = reachable_lists_.at(start);
		const auto finish_pos = reachable_stations.lower_bound(finish);
		if (finish_pos != end(reachable_stations)) {
			result = min(result, abs(finish - *finish_pos));
		}
		if (finish_pos != begin(reachable_stations)) {
			result = min(result, abs(finish - *prev(finish_pos)));
		}
		return result;
	}
private:
	map<int, set<int>> reachable_lists_;
};


int main() {
	RouteManager routes;
	string line = "ADD -2 5 ADD 10 4 ADD 5 8 GO 4 10 GO 4 -2 GO 5 0 GO 5 100";
	stringstream ss(line);
	int query_count = 7;
	//cin >> query_count;
	LOG_DURATION("Total")
	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		ss >> query_type;
		int start, finish;
		ss >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO") {
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}