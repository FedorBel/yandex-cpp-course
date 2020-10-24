#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <memory>

#define PI 3.14

using namespace std;

class Figure
{
public:
	virtual string Name() const = 0;
	virtual float Perimeter() const = 0;
	virtual float Area() const = 0;
};

class Triangle : public Figure
{
public:
	Triangle(const string& name, const float& a,
		const float& b, const float& c)
	{
		this->name = name;
		this->a = a;
		this->b = b;
		this->c = c;
	}

	string Name() const override { return name; }

	float Perimeter() const override
	{
		return a + b + c;
	}

	float Area() const override
	{
		float p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

private:
	string name;
	float a, b, c = 0;
};

class Rect : public Figure
{
public:
	Rect(const string& name, const float& width, const float& height)
	{
		this->name = name;
		this->width = width;
		this->height = height;
	}
	string Name() const override { return name; }

	float Perimeter() const override
	{
		return (width + height) * 2;
	}

	float Area() const override
	{
		return width * height;
	}

private:
	string name;
	float width, height = 0;
};

class Circle : public Figure
{
public:

	Circle(const string& name, const float& r)
	{
		this->name = name;
		this->r = r;
	}

	string Name() const override { return name; }

	float Perimeter() const override
	{
		return 2 * PI * r;
	}

	float Area() const override
	{
		return PI * r *r;
	}

private:
	string name;
	float r = 0;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
	string type;
	is >> type;
	if (type == "TRIANGLE")
	{
		float a, b, c = 0;
		is >> a >> b >> c;
		return make_shared<Triangle>(type, a, b, c);
	}

	if (type == "RECT")
	{
		float width, height = 0;
		is >> width >> height;
		return make_shared<Rect>(type, width, height);
	}

	if (type == "CIRCLE")
	{
		float r = 0;
		is >> r;
		return make_shared<Circle >(type, r);
	}
	return 0;
}

int main()
{
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}

	return 0;
}