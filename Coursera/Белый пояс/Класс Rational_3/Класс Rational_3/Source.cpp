#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

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

int main() {
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
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
