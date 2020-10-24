#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <iomanip>

using namespace std;

vector<int> Change_slow(int money, vector<int> c)
{
	vector<int> change(c.size());
	while (money > 0)
	{
		int coin = 0;
		auto max_coin_it = std::find_if(c.begin(), c.end(), [money](int i) {
			return i <= money;
		});
		if (max_coin_it != c.end())
		{
			coin = *max_coin_it;
			change[std::distance(c.begin(), max_coin_it)]++;
		}
		money -= coin;
	}
	return change;
}

vector<int> Change_fast(int money, vector<int> c)
{
	int denominations_size = c.size();
	vector<int> change(c.size());
	int r = money;
	for (size_t k = 0; k < denominations_size; k++)
	{
		change[k] = r / c[k];
		r = r - c[k] * change[k];
	}
	return change;
}

int main()
{
	vector<int> denominations{ 10, 5, 2, 1 };
	setlocale(0, "");

	int money = 0;
	while (cout << "Введите сумму: " && cin >> money)
	{
		auto change_list = Change_fast(money, denominations);
		int total = 0;
		cout << "==============================================" << endl;
		cout << setw(15) << left << "Номиналы";
		for (const auto el : denominations)
		{
			cout << setw(5) << el << " ";
		}
		cout << endl;
		cout << setw(15) << left << "Кол-во монет";
		for (size_t i = 0; i < denominations.size(); i++)
		{			 
			cout << setw(5) << change_list[i] << " ";
			total += (denominations[i] * change_list[i]);
		}
		cout << endl;
		cout << setw(15) << "Total: " << total << endl;
		cout << "==============================================" << endl;
	}

	return 0;
}