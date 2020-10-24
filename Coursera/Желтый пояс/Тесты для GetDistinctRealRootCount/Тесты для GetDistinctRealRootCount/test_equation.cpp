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

void SolveQuadradicEqualation(double a, double b, double c, int& root_count)
{
	int d = b * b - 4 * a * c;
	if (d > 0)
	{
		root_count = 2;
	}
	else if (d == 0)
	{
		root_count = 1;
	}
}

void SolveLinearEqualation(double b, double c, int& root_count)
{
	if (b != 0)
	{
		root_count = 1;
	}
}

int GetDistinctRealRootCount(double a, double b, double c) {
	int root_count = 0;
	if (a != 0)
	{
		SolveQuadradicEqualation(a, b, c, root_count);
	}
	else
	{
		SolveLinearEqualation(b, c, root_count);
	}
	return root_count;
}

void TestRootCount()
{
	AssertEqual(GetDistinctRealRootCount(1, 2, 3), 0);
	AssertEqual(GetDistinctRealRootCount(4, 8, 3), 2);
	AssertEqual(GetDistinctRealRootCount(0, 0, 3), 0);
	AssertEqual(GetDistinctRealRootCount(5, 0, 0), 1);
	AssertEqual(GetDistinctRealRootCount(0, 2, 0), 1);
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRootCount, "TestRootCount");
	
	return 0;
}
