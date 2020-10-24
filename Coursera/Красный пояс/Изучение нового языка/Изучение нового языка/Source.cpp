#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>

#include "profile.h"

using namespace std;

class Learner {
private:
	set<string> dict;

public:
	int Learn(const vector<string>& words) {
		int newWords = 0;
		for (const auto& word : words) {
			if (!dict.count(word) || dict.empty())
			{
				newWords++;
			}
			
			dict.insert(word);
		}
		return newWords;
	}

	vector<string> KnownWords() {
		vector<string> result;
		for (const auto& w : dict)
		{
			result.push_back(w);
		}
		return result;
	}
};

int main()
{
	LOG_DURATION("Total")
	Learner learner;
	string line;
	/*while (getline(cin, line)) {
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
		}
		cout << learner.Learn(words) << "\n";
	}*/

	line = "get give let let go keep make put seem take take be do have say";
	vector<string> words;
	stringstream ss(line);
	string word;
	while (ss >> word) {
		words.push_back(word);
	}
	cout << learner.Learn(words) << "\n";

	cout << "=== known words ===\n";
	for (auto word : learner.KnownWords()) {
		cout << word << "\n";
	}

	return 0;
}