#include "test_runner.h"

#include <vector>

using namespace std;

// ��������� Sentence<Token> ��� ������������� ���� Token
// ��������� vector<Token>.
// ��������� ����� � �������� ������������� ��������
// ������� ����� ������� �� ������������ ������ ��������,
// � ������ ����������� � vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// ����� Token ����� ����� bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> sentences;
	Sentence<Token> current_sentence;

	bool prev_isEnd = false;

	for (auto& token : tokens)
	{
		if (!token.IsEndSentencePunctuation() && token.IsEndSentencePunctuation() != prev_isEnd)
		{
			sentences.push_back(std::move(current_sentence));
		}
		current_sentence.push_back(std::move(token));
		prev_isEnd = token.IsEndSentencePunctuation();
	}

	if (!current_sentence.empty())
		sentences.push_back(std::move(current_sentence));

	return sentences;
}


struct TestToken {
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
		return is_end_sentence_punctuation;
	}
	bool operator==(const TestToken& other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

ostream& operator<<(ostream& stream, const TestToken& token) {
	return stream << token.data;
}

// ���� �������� ����������� �������� ������ TestToken.
// ��� �������� ���������� ����������� � ������� SplitIntoSentences
// ���������� �������� ��������� ����.
void TestSplitting() {
	auto test = SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} }));
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!"}}
			})
	);

	auto test2 = SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} }));
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
			})
	);

	auto test3 = SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} }));
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
			{{"Without"}, {"copies"}, {".", true}},
			})
			);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}
