#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <fstream>

using namespace std;

int main()
{
	ifstream input("input.txt");
	string line;

	while (getline(input, line))
	{
		cout << line << endl;
	}


	return 0;
}