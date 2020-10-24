#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	float a, b, c, d = 0;
	float x1, x2 = 0;
	cin >> a >> b >> c;

	if (a != 0 && b !=0)
	{
		d = pow(b, 2) - 4 * a*c;
		if (d > 0)
		{
			x1 = (-b + sqrt(d)) / (2 * a);
			x2 = (-b - sqrt(d)) / (2 * a);
			cout << x1 << " " << x2;
		}
		else if (d == 0)
		{
			x1 = -b / (2 * a);
			cout << x1;
		}
	}
	else if (a != 0)
	{
		int tmp = -c / a;
		if (tmp > 0)
		{
			x1 = sqrt(tmp);
			x2 = -sqrt(tmp);
			cout << x1 << " " << x2;
		}
	}
	else if (b != 0)
	{
		x1 = -c / b;
		cout << x1;
	}

	
	
	return 0;
}