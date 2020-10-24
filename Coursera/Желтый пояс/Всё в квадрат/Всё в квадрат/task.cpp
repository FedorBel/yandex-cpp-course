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
