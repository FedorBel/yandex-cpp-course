#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
	vector<string> result;
	for (auto i = s.begin(); i != s.end();)
	{				
		auto border = find(i, s.end(), ' ');		
		result.push_back({ i, border });	
		if (border == s.end())
		{
			break;
		}
		i = ++border;		
	}
	
	return result;
}

int main()
{
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}