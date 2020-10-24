#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

void command(vector<int>& queue, string com, int num, int& worry_count);
void command(const int& worry_count);

enum {QUIET, WORRY};

int main()
{
	int q;
	int ind;
	int worry_count = 0;
	string com;
	cin >> q;
	vector<int> queue;

	for (int i = 0; i < q; i++)
	{
		cin >> com;
		if (com== "WORRY_COUNT")
		{
			command(worry_count);
		}
		else
		{
			cin >> ind;
			command(queue, com, ind, worry_count);
		}
	}

	return 0;
}

void command(vector<int>& queue, string com, int num, int& worry_count)
{
	if (com=="COME")
	{
		if (num >= 0)
		{
			for (int i = 0; i < num; i++)
			{
				queue.push_back(QUIET);
			}
		}
		else
		{
			num = -num;
			for (int i = 0; i < num; i++)
			{
				if (queue[queue.size()-1]==WORRY)
				{
					worry_count--;
				}
				queue.pop_back();
			}
		}
	}
	else if (com == "WORRY")
	{
		queue[num] = WORRY;
		worry_count++;
	}
	else if (com == "QUIET")
	{
		queue[num] = QUIET;
		worry_count--;
	}
	else if (com == "WORRY_COUNT")
	{
		cout << worry_count << endl;
	}
}

void command(const int& worry_count)
{
	cout << worry_count << endl;
}