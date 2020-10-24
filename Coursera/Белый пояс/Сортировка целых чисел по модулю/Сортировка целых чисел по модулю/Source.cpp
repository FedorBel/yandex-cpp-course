#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>


using namespace std;

void Print(const vector<int>& v);

int main()
{
	int n;
	int a;
	vector<int> v;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> a;
		v.push_back(a);
	}

	sort(begin(v), end(v), [](int i, int j) {return (abs(i) < abs(j)); });

	Print(v);

	return 0;
}

void Print(const vector<int>& v)
{
	for (auto& i : v)
	{
		cout << i << " ";
	}
}
