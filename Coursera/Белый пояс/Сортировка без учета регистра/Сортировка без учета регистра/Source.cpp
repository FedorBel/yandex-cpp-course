#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

bool LowerCase(string i, string j);

int main()
{
	int n;
	string str;

	vector<string> v;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		v.push_back(str);
	}

	sort(v.begin(), v.end(), LowerCase);

	for (const auto& i : v)
	{
		cout << i << " ";
	}


	return 0;
}

bool LowerCase(string i, string j)
{
	string tmp1 = i;
	string tmp2 = j;
	for (auto& it : tmp1)
	{
		it = (char)tolower((int)it);
	}
	for (auto& it : tmp2)
	{
		it = (char)tolower((int)it);
	}
	return tmp1<tmp2;
}
