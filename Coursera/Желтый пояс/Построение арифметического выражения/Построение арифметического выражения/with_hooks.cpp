#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <deque>

using namespace std;

/*enum class BinarOper
{
	PLUS,
	MINUS,
	MULT,
	DIV
};

struct Operation
{
	BinarOper oper;
	string num;
};

istream& operator>>(istream& is, Operation& op)
{
	int
	is >> op.oper;
}*/
/*enum class Priority
{
	LOW,
	HIGH
};*/

int main()
{
	deque<string> d;
	int n;
	string x;
	cin >> x >> n;
	cin.get();
	d.push_back(x);
	int old_priority = 0; // LOW
	for (int i = 0; i < n; i++)
	{		
		string operation;				
		getline(cin, operation);
		if (operation.size() == 0)
		{
			continue;
		}

		int new_priority = 0;

		if (operation[0] == '*' || operation[0] == '/')
		{
			new_priority = 1; // HIGH
		}

		if (i = 0)
		{
			old_priority = new_priority;
		}

		/*switch (new_priority)
		{
		case Priority::LOW:

		}*/

		if (new_priority > old_priority)
		{
			d.push_front("(");
			d.push_back(") ");
			d.push_back(operation);
		}
		else
		{			
			d.push_back(" ");
			d.push_back(operation);
		}		
		old_priority = new_priority;
	}

	for (const auto& i : d)
	{
		cout << i;
	}
	cout << endl;

	return 0;
}