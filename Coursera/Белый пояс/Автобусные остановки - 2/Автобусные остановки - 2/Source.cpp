#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void create_route(map<vector<string>, int>& bus_route, int& id);

int main()
{
	int q;
	int id = 1;
	cin >> q;
	map<vector<string>, int> bus_route;
	for (int i = 0; i < q; i++)
	{
		create_route(bus_route, id);
	}

	return 0;
}

void create_route(map<vector<string>, int>& bus_route, int & id)
{
	vector<string> route;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string stop;
		cin >> stop;
		route.push_back(stop);
	}
	if (bus_route.find(route) != bus_route.end())
	{
		cout << "Already exists for " << bus_route.find(route)->second << endl;
	}
	else
	{
		cout << "New bus " << id << endl;
		bus_route[route] = id++;
	}
}
