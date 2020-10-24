#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class ReversibleString
{
public:
	ReversibleString() {}
	ReversibleString(const string& new_str)
	{
		str = new_str;
	}
	string ToString() const { return str; }

	/*void Reverse()
	{
		string tmp;
		for (auto i = str.rbegin(); i != str.rend(); i++)
		{
			tmp += *i;
		}
		str = tmp;
	}*/

	void Reverse() // Лучше так
	{
		reverse(begin(str), end(str));
	}

private:

	string str;
};

int main()
{
	ReversibleString s("live");
	s.Reverse();
	cout << s.ToString() << endl;

	s.Reverse();
	const ReversibleString& s_ref = s;
	string tmp = s_ref.ToString();
	cout << tmp << endl;

	ReversibleString empty;
	cout << '"' << empty.ToString() << '"' << endl;

	return 0;
}