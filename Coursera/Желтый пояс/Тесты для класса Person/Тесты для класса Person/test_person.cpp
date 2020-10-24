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

void TestIncognito()
{
	Person p;
	AssertEqual(p.GetFullName(1), "Incognito");
	AssertEqual(p.GetFullName(-1), "Incognito");
	AssertEqual(p.GetFullName(1638), "Incognito");
}

void TestFirstName()
{
	Person p;
	p.ChangeFirstName(1, "Ann");
	AssertEqual(p.GetFullName(1), "Ann with unknown last name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Ann with unknown last name");

	p.ChangeFirstName(6, "Annabel");
	AssertEqual(p.GetFullName(1), "Ann with unknown last name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Ann with unknown last name");
	AssertEqual(p.GetFullName(6), "Annabel with unknown last name");

	p.ChangeFirstName(3, "Anya");
	AssertEqual(p.GetFullName(1), "Ann with unknown last name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Anya with unknown last name");
	AssertEqual(p.GetFullName(6), "Annabel with unknown last name");
}

void TestLastName()
{
	Person p;
	p.ChangeLastName(1, "Terd");
	AssertEqual(p.GetFullName(1), "Terd with unknown first name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Terd with unknown first name");

	p.ChangeLastName(6, "Terdincton");
	AssertEqual(p.GetFullName(1), "Terd with unknown first name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Terd with unknown first name");
	AssertEqual(p.GetFullName(6), "Terdincton with unknown first name");

	p.ChangeLastName(3, "Terdessa");
	AssertEqual(p.GetFullName(1), "Terd with unknown first name");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Terdessa with unknown first name");
	AssertEqual(p.GetFullName(6), "Terdincton with unknown first name");
}

void TestFullName()
{
	Person p;
	p.ChangeFirstName(1, "Ann");
	p.ChangeLastName(1, "Terd");
	AssertEqual(p.GetFullName(1), "Ann Terd");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Ann Terd");

	p.ChangeFirstName(6, "Annabel");
	p.ChangeLastName(7, "Terdincton");
	AssertEqual(p.GetFullName(1), "Ann Terd");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Ann Terd");
	AssertEqual(p.GetFullName(6), "Annabel Terd");
	AssertEqual(p.GetFullName(7), "Annabel Terdincton");
	AssertEqual(p.GetFullName(8), "Annabel Terdincton");

	p.ChangeFirstName(3, "Anya");
	p.ChangeLastName(4, "Terdessa");
	AssertEqual(p.GetFullName(1), "Ann Terd");
	AssertEqual(p.GetFullName(0), "Incognito");
	AssertEqual(p.GetFullName(5), "Anya Terdessa");
	AssertEqual(p.GetFullName(6), "Annabel Terdessa");
	AssertEqual(p.GetFullName(7), "Annabel Terdincton");
	AssertEqual(p.GetFullName(8), "Annabel Terdincton");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestIncognito, "TestIncognito");
	runner.RunTest(TestFirstName, "TestFirstName");
	runner.RunTest(TestLastName, "TestLastName");
	runner.RunTest(TestFullName, "TestFullName");
	return 0;
}
