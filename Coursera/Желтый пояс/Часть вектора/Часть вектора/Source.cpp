#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
	auto neg = find_if(numbers.begin(), numbers.end(), 
		[](const int& num) {
		return num < 0;
	});

	while (neg != numbers.begin())
	{
		--neg;
		cout << *neg << " ";
	}	
}

int main()
{
	PrintVectorPart({ 6, 1, 8, -5, 4 });
	cout << endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	cout << endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	cout << endl;

	return 0;
}