#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <functional>
using namespace std;

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other)
	{
		for (const auto& el : other.word_frequences)
		{
			word_frequences[el.first] += el.second;
		}
	}
};

/*
Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats stats;
	
	for (const auto& word : key_words)
	{		
		auto pos = line.find(word);
		while (pos != line.npos)
		{
			if (pos > 0 && pos < line.size() - 1 - word.size())
			{
				if (line[pos - 1] == line[pos + word.size()] && line[pos - 1] == ' ')
				{					
					++stats.word_frequences[word];
				}
			}
			else if (pos == 0)
			{
				if (line[pos + word.size()] == ' ')
				{
					++stats.word_frequences[word];
				}
			}
			else if (pos == line.size() - word.size() && pos > 0)
			{
				if (line[pos - 1] == ' ')
				{
					++stats.word_frequences[word];
				}
			}
			pos = line.find(word, pos +1);			
		}
	}

	return stats;
}
*/

Stats ExploreLine(const set<string>& key_words, const string& line) {
	string::const_iterator first = line.begin();
	string::const_iterator last = line.end();
	Stats result;
	string::const_iterator it;
	while ((it = find(first, last, ' ')) <= last) {
		string word(first, it);
		if (*key_words.lower_bound(word) == word) {
			result.word_frequences[word]++;
		}
		if (it != last) first = it + 1;
		else break;
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
	const set<string>& key_words, istream& input
) {
	Stats result;
	for (string line; getline(input, line); ) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWordsSingleThreadForVector(
	const set<string>& key_words, vector<string> publications
) {
	Stats result;
	for (auto& publication : publications) {
		result += ExploreLine(key_words, publication);
	}
	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	vector<future<Stats>> futures;	

	vector<string> publications;
	string publication;

	const int page_size = 10000;

	int i = 0;

	while (getline(input, publication))
	{		
		publications.push_back(move(publication));
		i++;
		if (i == page_size)
		{
			futures.push_back(async(ExploreKeyWordsSingleThreadForVector, ref(key_words), move(publications)));
			i = 0;
		}
	}
	Stats result = ExploreKeyWordsSingleThreadForVector(key_words, move(publications));
	/*
	for (auto& sentences : Paginate(publications, 2000))
	{
		vector<string> page = { make_move_iterator(sentences.begin()), make_move_iterator(sentences.end()) };
		//Stats result = ExploreKeyWordsSingleThreadForVector(key_words, page);
		futures.push_back(async(ExploreKeyWordsSingleThreadForVector, ref(key_words), move(page)));
	}	*/

	//Stats result;
	
	for (auto& f : futures) {
		result += f.get();
	}

	return result;
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}

