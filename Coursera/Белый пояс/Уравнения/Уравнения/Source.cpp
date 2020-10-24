#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	while (true)
	{
		float a, b, c, d, x1, x2;

		cin >> a >> b >> c;
		if (a != 0 && b != 0)
		{

			d = b * b - 4 * a * c;
			if (d > 0)
			{
				x2 = (-b - sqrt(d)) / (2 * a);
				x1 = (-b + sqrt(d)) / (2 * a);
				cout << x1 << " " << x2 << endl;
			}
			else if (d == 0)
			{
				x1 = (-b) / (2 * a);
				cout << x1 << endl;
			}
		}
		else if (b != 0)
		{
			x1 = -c / b;
			if (x1 == -0)
				x1 = 0;
			cout << x1 << endl;
		}
		else if (a != 0)
		{
			float tmp = -c / a;
			if (tmp == -0)
				tmp = 0;

			if (tmp > 0)
			{
				x1 = sqrt(tmp);
	
				cout << x1 << endl;
				cout << -x1 << endl;
			}
			else if (tmp == 0)
			{
				cout << 0 << endl;
			}
		}
		cout << endl;
	}
	
	return 0;
}