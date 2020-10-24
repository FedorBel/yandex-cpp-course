#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class SortedStrings {
public:
	void AddString(const string& s) 
	{
		v.push_back(s);
		sort(v.begin(), v.end());
	}
	vector<string> GetSortedStrings() 
	{
		return v;
	}
private:
	vector<string> v;
};

void PrintSortedStrings(SortedStrings& strings)
{
	for (const string& s : strings.GetSortedStrings()) 
	{
		cout << s << " ";
	}
	cout << endl;
}

int main() {
	SortedStrings strings;

	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);

	strings.AddString("second");
	PrintSortedStrings(strings);

	return 0;
}