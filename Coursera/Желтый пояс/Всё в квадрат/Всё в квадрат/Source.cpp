#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <utility>

using namespace std;

template<typename T> T Sqr(T x);
template<typename T> vector<T> Sqr(vector<T> x);
template<typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& x);
template<typename First, typename Second> map<First, Second> Sqr(map<First, Second> x);

int main()
{
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<string, int> m = { {"one", 1}, {"two",2} };
	Sqr(m);

	for (const auto& i : Sqr(m))
	{
		cout << i.first << " " << i.second << endl;
	}

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}

template<typename T>
T Sqr(T x)
{
	return x * x;
}

template<typename T>
vector<T> Sqr(vector<T> x)
{	
	for (auto& i : x)
	{
		i = Sqr(i);
	}

	return x;
}

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& x)
{	
	return pair<First, Second>(Sqr(x.first), Sqr(x.second));
}

template<typename First, typename Second>
map<First, Second> Sqr(map<First, Second> x)
{
	
	for (auto& i : x)
	{
		i.second = Sqr(i.second);
	}	
	
	return x;	
}


