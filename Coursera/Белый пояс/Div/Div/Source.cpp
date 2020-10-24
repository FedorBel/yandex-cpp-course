#include <iostream>
#include <string>

using namespace std;
// Поиск f
int main()
{
	string a;
	cin >> a;

	int count = 0;
	int index;

	for (int i = 0; i < a.size(); i++)
	{
		if (a[i]=='f')
		{
			count++;
			index = i;
		}
		if (count==2)
		{
			cout << index;
			break;
		}
	}
	if (count==1)
	{
		cout << -1;
	}
	else if (count == 0)
	{
		cout << -2;
	}
	
	return 0;
}