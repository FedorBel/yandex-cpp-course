#include <iostream>

using namespace std;

int Factorial(int n);

int main()
{
	int a;
	int n;
	cin >> a;
	n = Factorial(a);
	cout << n;

	return 0;
}

int Factorial(int n)
{
	if (n==1)
	{
		return 1;
	}
	else if (n==0)
	{
		return 1;
	}
	else if (n < 0)
	{
		return 1;
	}

	return n * Factorial(n - 1);
}
