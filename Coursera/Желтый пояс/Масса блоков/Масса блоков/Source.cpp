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
	int n, r = 0;
	uint64_t w, h, d = 0;
	uint64_t v = 0;
	uint64_t m = 0;
	uint64_t sum_m = 0;

	cin >> n >> r;

	for (int i = 0; i < n; i++)
	{
		cin >> w >> h >> d;
		v = w * h * d;
		m = v * r;
		sum_m += m;
	}

	cout << sum_m << endl;

	return 0;
}