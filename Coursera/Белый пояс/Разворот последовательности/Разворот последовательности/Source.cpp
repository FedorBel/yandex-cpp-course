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

// Мой вариант
/*void Reverse(vector<int>& v)
{
	vector<int> tmp;

	for (int j = v.size()-1; j >= 0; j--)
	{
		tmp.push_back(v[j]);
	}
	v = tmp;
}*/

// Более хорошая реализация
void Reverse(vector<int>& v) {
	int n = v.size();  // для удобства сохраним размер вектора в переменную n
	for (int i = 0; i < n / 2; ++i) {
		// элемент с индексом i симметричен элементу с индексом n - 1 - i
		// поменяем их местами с помощью временной переменной tmp
		int tmp = v[i];
		v[i] = v[n - 1 - i];
		v[n - 1 - i] = tmp;
	}
}
