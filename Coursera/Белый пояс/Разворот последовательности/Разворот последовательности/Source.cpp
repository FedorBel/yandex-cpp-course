#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

void Reverse(vector<int>& v);

int main()
{
	vector<int> numbers = { 1, 5, 3, 4, 2 };
	Reverse(numbers);

	return 0;
}

// ��� �������
/*void Reverse(vector<int>& v)
{
	vector<int> tmp;

	for (int j = v.size()-1; j >= 0; j--)
	{
		tmp.push_back(v[j]);
	}
	v = tmp;
}*/

// ����� ������� ����������
void Reverse(vector<int>& v) {
	int n = v.size();  // ��� �������� �������� ������ ������� � ���������� n
	for (int i = 0; i < n / 2; ++i) {
		// ������� � �������� i ����������� �������� � �������� n - 1 - i
		// �������� �� ������� � ������� ��������� ���������� tmp
		int tmp = v[i];
		v[i] = v[n - 1 - i];
		v[n - 1 - i] = tmp;
	}
}
