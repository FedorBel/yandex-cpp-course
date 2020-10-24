#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void command(map<string, string>& dict);

int main()
{
	int q;
	map<string, string> dict;
	//vector<set<string>> mySet;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		command(dict);
	}

	return 0;
}

void command(map<string, string>& dict)
{
	string com;
	cin >> com;

	if (com == "ADD")
	{
		string word1, word2;
		
		cin >> word1 >> word2;
		dict[word1] = word2;
		
		
	}
	else if (com == "COUNT")
	{
		string word;
		cin >> word;
		map<string, string> reverse_dict;
		for (auto words : dict)
		{
			reverse_dict[words.second] = words.first;
		}
		
		int num1 = dict.count(word);
		int num2 = reverse_dict.count(word);
		cout << num1+num2 << endl;
	}
	else if (com == "CHECK")
	{
		string word1, word2;
		cin >> word1 >> word2;

		map<string, string> reverse_dict;
		for (auto words : dict)
		{
			reverse_dict[words.second] = words.first;
		}

		string tmp1 = "-1";
		string tmp2 = "-1";

		if (dict.find(word1)!=dict.end())
		{
			tmp1 = dict.find(word1)->second;
		}
		if (reverse_dict.find(word1) != reverse_dict.end())
		{
			tmp2 = reverse_dict.find(word1)->second;
		}

		if (tmp1==word2 || tmp2==word2)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}

}