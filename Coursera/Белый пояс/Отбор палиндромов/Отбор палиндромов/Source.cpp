#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string s);
vector<string> PalindromFilter(vector<string> words, int minLength);

int main()
{
	vector<string> str = { "weew","bro","code" };
	vector<string> s = PalindromFilter(str, 4);

	return 0;
}

bool IsPalindrom(string s) {

	for (size_t i = 0; i < s.size() / 2; ++i) {
		if (s[i] != s[s.size() - i - 1]) {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> palindroms;
	for (auto w : words)
	{
		if (IsPalindrom(w) && w.size() >= minLength)
		{
			palindroms.push_back(w);
		}
	}

	return palindroms;
}
