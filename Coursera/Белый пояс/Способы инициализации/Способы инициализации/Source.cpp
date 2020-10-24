#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class Incognizable
{
public:
	Incognizable() {}
	Incognizable(int new_a) { a = new_a; }
	Incognizable(int new_a, int new_b) { a = new_a; b = new_b; }

private:
	int a;
	int b;
};

int main()
{
	Incognizable a;
	Incognizable b = {};
	Incognizable c = { 0 };
	Incognizable d = { 0, 1 };

	return 0;
}