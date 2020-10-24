#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

bool IsPalindrom(string str)
{
	string str2;
	str2.resize(str.size());
	for (int i = 0, j = str.size() - 1; i < str.size(); i++, j--)
	{
		str2[i] = str[j];
	}

	if (str == str2)
	{
		return true;
	}
	return false;
}

void IsPalindr()
{
	AssertEqual(IsPalindrom(""), 1);
	AssertEqual(IsPalindrom("m"), 1);
	AssertEqual(IsPalindrom("a"), 1);
	AssertEqual(IsPalindrom("am"), 0);
	AssertEqual(IsPalindrom("ama"), 1);
	AssertEqual(IsPalindrom("madam"), 1);
	AssertEqual(IsPalindrom("level"), 1);
	AssertEqual(IsPalindrom("wasitacaroracatisaw"), 1);
	AssertEqual(IsPalindrom("le el"), 1);
	AssertEqual(IsPalindrom("tachka"), 0);
	AssertEqual(IsPalindrom("hadam"), 0);
	AssertEqual(IsPalindrom("madah"), 0);
	AssertEqual(IsPalindrom("777777"), 1);
	AssertEqual(IsPalindrom("77777"), 1);
	AssertEqual(IsPalindrom("777778"), 0);
	AssertEqual(IsPalindrom("XabbaY"), 0);
}

int main() {
	TestRunner runner;
	runner.RunTest(IsPalindr, "IsPalindr");
	return 0;
}
