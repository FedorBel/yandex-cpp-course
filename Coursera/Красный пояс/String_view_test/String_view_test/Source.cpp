#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <string_view>
#include <sstream>

using namespace std;

/*
string ConcatenateSrtingVievs(string_view lhs, string_view rhs)
{
	ostringstream s;
	s << lhs << rhs;
	return s.str();
}*/

string ConcatenateSrtingVievs(string_view lhs, string_view rhs)
{	
	string s;
	return (s += lhs) += rhs;
}

int main()
{
	cout << ConcatenateSrtingVievs("hello ", "world") << endl;

	return 0;
}