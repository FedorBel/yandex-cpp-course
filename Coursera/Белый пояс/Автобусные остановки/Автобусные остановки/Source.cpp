#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void command(const string& com, map<string, vector<string>>& buses_route);

int main()
{
	int q;
	string com;
	map<string, vector<string>> buses_route;
	cin >> q;
	
	for (int i = 0; i < q; i++)
	{
		cin >> com;
		command(com, buses_route);
	}
	return 0;
}

void command(const string & com, map<string, vector<string>>& buses_route)
{
	if (com=="NEW_BUS")
	{
		int stop_count;
		string bus;
		string stop;
		cin >> bus >> stop_count;
		for (int i = 0; i < stop_count; i++)
		{
			cin >> stop;
			buses_route[bus].push_back(stop);
		}
	}
	else if (com == "BUSES_FOR_STOP")
	{
		string stop;
		cin >> stop;
		int count = 0;
		for (const auto& routes : buses_route)
		{
			if (find(routes.second.begin(), routes.second.end(), stop) != routes.second.end())
			{
				cout << routes.first << " ";
				count++;
			}
		}
		if (count==0)
		{
			cout << "No stop";
		}
		cout << endl;
	}
	else if (com == "STOPS_FOR_BUS") // Исправить
	{
		string bus;
		cin >> bus;
	
		if (buses_route.find(bus) != buses_route.end())
		{
			for (auto i = buses_route[bus].begin(); i != buses_route[bus].end(); ++i)
			{
				int count = 0;
				cout << "Stop " << *i << ": ";
				for (const auto& routes : buses_route)
				{
					if (find(routes.second.begin(), routes.second.end(), *i) != routes.second.end() && routes.first != bus)
					{
						cout << routes.first << " ";
						count++;
					}
				}
				if (count == 0)
				{
					cout << "no interchange";
				}
				cout << endl;
			}
		}
		else
		{
			cout << "No bus" << endl;
		}
	}
	else if (com == "ALL_BUSES")
	{
		if (buses_route.size() == 0)
		{
			cout << "No buses" << endl;
		}
		else
		{
			for (const auto& routes : buses_route)
			{
				cout << "Bus " << routes.first << ": ";
				for (auto i = buses_route[routes.first].begin(); i != buses_route[routes.first].end(); ++i)
				{
					cout << *i << " ";
				}
				cout << endl;
			}
		}
	}
}
