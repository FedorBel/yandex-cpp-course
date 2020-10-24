#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

vector<int> Reversed(const vector<int>& v);

int main()
{
	vector<int> numbers = { 1, 5, 3, 4, 2 };
	vector<int> numbers1 = Reversed(numbers);
	return 0;
}

vector<int> Reversed(const vector<int>& v)
{
	vector<int> tmp;

	for (int j = v.size() - 1; j >= 0; --j)
	{
		tmp.push_back(v[j]);
	}
	
	return tmp;
}
