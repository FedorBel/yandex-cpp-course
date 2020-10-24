#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

void command(const vector<int>& days_amount, vector<vector<string>>& day_work, int& current_month);
void command(const string& com, vector<vector<string>>& day_work);

int main()
{
	int q;
	int current_month = 0;
	string com;
	cin >> q;
	vector<int> days_amount = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	vector<vector<string>> day_work(31);
	for (int i = 0; i < q; i++)
	{
		cin >> com;
		if (com=="NEXT")
		{
			command(days_amount, day_work, current_month);
		}
		else
		{
			command(com, day_work);
		}
	}

	return 0;
}

void command(const vector<int>& days_amount, vector<vector<string>>& day_work, int& current_month)
{
	if (current_month==11)
	{
		current_month = 0;
	}
	else
	{
		current_month++;
	}
	vector<vector<string>> tmp = day_work;
	day_work.resize(days_amount[current_month]);
	if (day_work.size()<tmp.size())
	{
		for (int i = day_work.size(); i < tmp.size(); i++)
		{
			for (int j = 0; j < tmp[i].size(); j++)
			{
				day_work[day_work.size() - 1].push_back(tmp[i][j]);
			}
		}
	}
}

void command(const string& com, vector<vector<string>>& day_work)
{
	if (com=="ADD")
	{
		int day;
		string work;
		cin >> day;
		day--;
		cin >> work;
		day_work[day].push_back(work);		
	}
	else if (com == "DUMP")
	{
		int day;
		cin >> day;
		day--;
		cout << day_work[day].size() << " ";
		for (int i = 0; i < day_work[day].size(); i++)
		{
			cout << day_work[day][i] << " ";
		}
		cout << endl;
	}
}
