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
		while (!input.eof())
		{
			double num = 0;
			input >> num;
			cout << fixed << setprecision(3);
			cout << num << endl;
		}
	}

	return 0;
}