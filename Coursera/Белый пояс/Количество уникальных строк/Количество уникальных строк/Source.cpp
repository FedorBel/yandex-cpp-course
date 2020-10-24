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
	vector<string> s;
	int n;
	int num = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		s.push_back(str);
	}
	set<string> mySet(begin(s), end(s));	
	cout << mySet.size();

	return 0;
}