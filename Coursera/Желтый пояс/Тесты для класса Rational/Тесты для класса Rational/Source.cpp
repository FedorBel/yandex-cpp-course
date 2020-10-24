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

int calcNod(int a, int b)
{
	a = abs(a);
	b = abs(b);

	while (a > 0 && b > 0)
	{
		// возьмём большее из чисел и заменим его остатком от деления на второе
		// действительно, если a и b делятся на x, то a - b и b делятся на x
		// тогда и a % b и b делятся на x, так что можно a заменить на a % b

		if (a > b)
		{
			a %= b;
		}
		else
		{
			b %= a;
		}
	}

	return a + b;
}

int calcNok(int a, int b)
{
	return a * b*calcNod(a, b);
}

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int numerator, int denominator)
	{
		int nod = calcNod(numerator, denominator);
		if (numerator < 0 && denominator < 0)
		{
			numerator = abs(numerator);
			denominator = abs(denominator);
		}
		else if (denominator < 0)
		{
			denominator = abs(denominator);
			numerator = -numerator;
		}
		this->numerator = numerator / nod;
		this->denominator = denominator / nod;
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

	void SetNumerator(int numerator)
	{
		int nod = calcNod(numerator, denominator);
		if (numerator < 0 && denominator < 0)
		{
			numerator = abs(numerator);
			denominator = abs(denominator);
		}
		else if (denominator < 0)
		{
			denominator = abs(denominator);
			numerator = -numerator;
		}
		this->numerator = numerator / nod;
		this->denominator = denominator / nod;
	}

	void SetDenominator(int denominator)
	{
		int nod = calcNod(numerator, denominator);
		if (numerator < 0 && denominator < 0)
		{
			numerator = abs(numerator);
			denominator = abs(denominator);
		}
		else if (denominator < 0)
		{
			denominator = abs(denominator);
			numerator = -numerator;
		}
		this->numerator = numerator / nod;
		this->denominator = denominator / nod;
	}

private:
	int numerator;
	int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return (lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	int nok = calcNok(lhs.Denominator(), rhs.Denominator());
	int mult_lhs = nok / lhs.Denominator();
	int mult_rhs = nok / rhs.Denominator();
	int numerator = lhs.Numerator()*mult_lhs + rhs.Numerator()*mult_rhs;
	int denominator = lhs.Denominator()*mult_lhs;
	Rational result(numerator, denominator);
	return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	int nok = calcNok(lhs.Denominator(), rhs.Denominator());
	int mult_lhs = nok / lhs.Denominator();
	int mult_rhs = nok / rhs.Denominator();
	int numerator = lhs.Numerator()*mult_lhs - rhs.Numerator()*mult_rhs;
	int denominator = lhs.Denominator()*mult_lhs;
	Rational result(numerator, denominator);
	return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
}

istream& operator>>(istream& stream, Rational& rational)
{
	int numerator;
	int denominator;

	if (!stream.eof())
	{
		stream >> numerator;
		stream.ignore(1);
		stream >> denominator;
		rational.SetNumerator(numerator);
		rational.SetDenominator(denominator);
	}

	return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
	double tmp1 = (double)lhs.Numerator() / lhs.Denominator();
	double tmp2 = (double)rhs.Numerator() / rhs.Denominator();
	return (tmp1 < tmp2);
}

void TestDef()
{
	Rational r;
	AssertEqual(r.Numerator(), 0);
	AssertEqual(r.Denominator(), 1);
}

void TestMake()
{
	Rational r(1, 2);
	AssertEqual(r.Numerator(), 1);
	AssertEqual(r.Denominator(), 2);

	Rational r1(3, 6);
	AssertEqual(r1.Numerator(), 1);
	AssertEqual(r1.Denominator(), 2);

	Rational r2(0, 5);
	AssertEqual(r2.Numerator(), 0);
	AssertEqual(r2.Denominator(), 1);
}

void TestNegative()
{
	Rational r(-1, 2);
	AssertEqual(r.Numerator(), -1);
	AssertEqual(r.Denominator(), 2);

	Rational r1(1, -2);
	AssertEqual(r1.Numerator(), -1);
	AssertEqual(r1.Denominator(), 2);

	Rational r2(-1, -2);
	AssertEqual(r2.Numerator(), 1);
	AssertEqual(r2.Denominator(), 2);

	Rational r3(-2, -3);
	AssertEqual(r3.Numerator(), 2);
	AssertEqual(r3.Denominator(), 3);
}

int main() {
	TestRunner runner;
	runner.RunTest(TestDef, "TestDef");
	runner.RunTest(TestMake, "TestMake");
	runner.RunTest(TestNegative, "TestNegative");
	return 0;
}
