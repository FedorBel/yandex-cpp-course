#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int a;
	int tmp;
	vector<int> dv;
	cin >> a;

	while (a!=0)
	{
		tmp = a % 2;
		a /= 2;
		if (dv.size()==0)
		{
			dv.push_back(tmp);
		}
		else
		{
			dv.insert(dv.begin(), tmp);
		}
	}

	for (auto c:dv)
	{
		cout << c;
	}

	return 0;
}