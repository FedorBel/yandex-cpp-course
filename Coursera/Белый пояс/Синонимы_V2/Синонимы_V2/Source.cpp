#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

void command(map<string, set<string>>& dict);

int main()
{
	int q;
	map<string, set<string>> dict;
	//vector<set<string>> mySet;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		command(dict);
	}

	return 0;
}

void command(map<string, set<string>>& dict)
{
	string com;
	cin >> com;

	if (com == "ADD")
	{
		string word1, word2;

		cin >> word1 >> word2;
		dict[word1].insert(word2);
		dict[word2].insert(word1);


	}
	else if (com == "COUNT")
	{
		string word;
		cin >> word;

		cout << dict[word].size() << endl;
	}
	else if (com == "CHECK")
	{
		string word1, word2;
		cin >> word1 >> word2;

		if (dict[word1].find(word2) != dict[word1].end())
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}

		
	}

}