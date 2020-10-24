#include <iostream>

using namespace std;

void UpdateIfGreater(int a, int& b);

int main()
{
	int a = 0;
	UpdateIfGreater(2, a);

	return 0;
}

void UpdateIfGreater(int a, int& b)
{
	if (a>b)
	{
		b = a;
	}
}
