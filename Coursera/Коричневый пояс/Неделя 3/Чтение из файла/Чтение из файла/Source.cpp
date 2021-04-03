#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <fstream>

#include "json.h"

using namespace std;

int main()
{
	ifstream in("text.txt");
	if (in.is_open())
	{
		cout << "File opened" << endl;
		auto doc = json::Load(in);
		for (const auto& el : doc.GetRoot().AsMap())
		{
			cout << el.second.AsDouble() << endl;
		}
	}
	else
	{
		cout << "Error" << endl;
	}
	return 0;
}