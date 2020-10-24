#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <numeric>

using namespace std;

int main()
{
	int num;
	cin >> num;
	vector<int> v(num);
	/*for (int i = num; i > 0; i--)
	{
		v.push_back(i);
	}*/
	iota(v.begin(), v.end(), 1); // Заполнить массив цифрами
	reverse(v.begin(), v.end());
	do
	{
		for (const auto& i : v)
		{
			cout << i << " ";
		}
		cout << endl;
	} while (prev_permutation(v.begin(), v.end()));

	return 0;
}