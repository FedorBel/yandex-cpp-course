#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void EnsureEqual(const string& left, const string& right);

void EnsureEqual(const string & left, const string & right)
{
	if (left != right)
	{
		throw runtime_error(left + " != " + right);
	}
}
