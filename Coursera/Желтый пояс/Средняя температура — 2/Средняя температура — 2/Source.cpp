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
	int n;
	int64_t sum = 0;

	cin >> n;

	vector<int> days_temp(n);

	for (auto& d : days_temp)
	{
		cin >> d;
		sum += d;
	}
	
	int avg_temp = sum / n;

	vector<int> hot_days;

	for (int i = 0; i < days_temp.size(); i++)
	{
		if (days_temp[i] > avg_temp)
		{
			hot_days.push_back(i);
		}
	}

	cout << hot_days.size() << endl;
	for (const auto& d : hot_days)
	{
		cout << d << " ";
	}
	cout << endl;

	return 0;
}