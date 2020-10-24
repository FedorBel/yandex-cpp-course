#include <iostream>
#include <string>

using namespace std;

bool IsPalindrom(string str);

int main()
{
	string str;
	cin >> str;
	cout << IsPalindrom(str);

	return 0;
}

bool IsPalindrom(string str)
{
	string str2;
	str2.resize(str.size());
	for (int i = 0, j = str.size() - 1; i < str.size(); i++, j--)
	{
		str2[i] = str[j];		
	}

	if (str==str2)
	{
		return true;
	}
	return false;
}
