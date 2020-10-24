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
	ofstream output("output.txt");
	if (output)
	{
		if (input)
		{
			while (getline(input, line))
			{
				output << line << endl;
			}
		}
	}

	return 0;
}