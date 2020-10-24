#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ((range_end - range_begin) < 2)
	{
		return;
	}

	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	
	auto begin = elements.begin();
	auto mid_begin = elements.begin() + elements.size() / 3;
	auto mid_end = elements.end() - elements.size() / 3;
	auto end = elements.end();
	//vector<typename RandomIt::value_type> lhs(range_begin, border);
	//vector<typename RandomIt::value_type> rhs(border, range_end);
	MergeSort(begin, mid_begin);
	MergeSort(mid_begin, mid_end);
	MergeSort(mid_end, end);
	vector<typename RandomIt::value_type> tmp;
	merge(begin, mid_begin, mid_begin, mid_end, back_inserter(tmp));
	auto tmp_begin = tmp.begin();
	auto tmp_end = tmp.end();
	merge(tmp_begin, tmp_end, mid_end, end, range_begin);
}

int main()
{
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}