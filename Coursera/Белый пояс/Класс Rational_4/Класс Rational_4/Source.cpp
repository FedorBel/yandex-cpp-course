#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <sstream>

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

istream& operator>>(istream& stream, Rational& input) {
	int a, b;
	stringstream temp;
	string line;
	stream >> line;
	if (line.empty()) return stream;
	temp << line;
	temp >> a;
	temp.ignore(1);
	temp >> b;
	input = { a, b };
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

int main() {
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
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