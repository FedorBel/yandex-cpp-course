#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
	auto it_border=find_if(elements.begin(), elements.end(),
		[border](T el) {
		return el > border;
	});
	vector<T> result;
	
	for (auto i = it_border; i != elements.end(); ++i)
	{		
		result.push_back(*i);
	}

	return result;
}

int main()
{
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;

	return 0;
}