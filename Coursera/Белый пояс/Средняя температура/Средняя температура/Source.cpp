#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

int main()
{
	int n;
	int sum = 0;
	int mid = 0;
	cin >> n;
	vector<int> v(n);
	vector<int> num;

	for (auto& a : v)
	{
		cin >> a;
		sum += a;
	}

	mid = sum / n;

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]>mid)
		{
			num.push_back(i);
		}
	}

	cout << num.size() << endl;
	for (auto a : num)
	{
		cout << a << " ";
	}

	return 0;
}