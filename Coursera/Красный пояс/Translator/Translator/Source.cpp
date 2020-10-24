#include "test_runner.h"
#include <string>
#include <vector>
#include <string_view>
#include <list>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target)
	{
		string_view s;
		string_view t;
		
		auto it_s = source_to_target.find(source);

		// Already have source in dict
		if (it_s != source_to_target.end())
		{
			auto to_del = it_s->second;
			target_to_source.erase(to_del);
			auto it_to_del = string_to_list[to_del];
			dict.erase(it_to_del);

			s = it_s->first;
		}
		else // Don't have source in dict
		{
			dict.push_back(static_cast<string>(source));
			s = dict.back();
			string_to_list[s] = prev(dict.end());			
		}

		auto it_t = target_to_source.find(target);

		// Already have target in dict
		if (it_t != target_to_source.end())
		{
			//auto to_del = it_s->second;
			//target_to_source.erase(to_del);
			//auto it_to_del = string_to_list[to_del];
			//dict.erase(it_to_del);

			t = it_t->first;
		}
		else // Don't have target in dict
		{
			dict.push_back(static_cast<string>(target));
			t = dict.back();
			string_to_list[t] = prev(dict.end());
		}

		// Fil dict with new pairs
		source_to_target[s] = t;
		target_to_source[t] = s;
	}

	string_view TranslateForward(string_view source) const
	{
		auto it = source_to_target.find(source);

		if (it != source_to_target.end())
		{
			return it->second;
		}
		else
		{
			return "";
		}		
	}

	string_view TranslateBackward(string_view target) const
	{
		auto it = target_to_source.find(target);

		if (it != target_to_source.end())
		{
			return it->second;
		}
		else
		{
			return "";
		}

	}

private:
	list<string> dict;
	map<string_view, string_view> source_to_target;
	map<string_view, string_view> target_to_source;
	map<string_view, list<string>::iterator> string_to_list;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("okno"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "table");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "okno");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}