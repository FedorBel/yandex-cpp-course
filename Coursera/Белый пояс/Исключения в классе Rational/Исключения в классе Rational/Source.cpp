#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <stdexcept>

using namespace std;

int calcNod(int a, int b);
int calcNok(int a, int b);

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw invalid_argument("");
		}
		else
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
		if (denominator == 0)
		{
			throw invalid_argument("");
		}
		else
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
	int denominator = lhs.Denominator() * rhs.Numerator();
	if (denominator == 0)
	{
		throw domain_error("");
	}
	else
	{
		return { lhs.Numerator() * rhs.Denominator(), denominator };
	}
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

int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}

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