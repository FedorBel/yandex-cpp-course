#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	ifstream input("input.txt");

	if (input)
	{
		int n = 0;
		int m = 0;
		input >> n >> m;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				int num = 0;
				input >> num;
				input.ignore(1);
				if (j == m - 1)
				{
					cout << setw(10) << num;
					continue;
				}
				cout << setw(10) << num << " ";
			}

			if (i == n - 1)
			{
				continue;
			}
			cout << endl;
		}

	}

	return 0;
}