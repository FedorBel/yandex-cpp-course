#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

template<typename T>
class Deque
{
public:
	bool Empty() const { return (front.empty() && back.empty()); }
	size_t Size() const { return front.size() + back.size(); }

	T& operator[](size_t index)
	{
		if (index < front.size())
		{
			return front[index];
		}
		else
		{
			index -= front.size();
			return back[index];
		}
	}

	const T& operator[](size_t index) const
	{
		if (index < front.size())
		{
			return front[index];
		}
		else
		{
			index -= front.size();
			return back[index];
		}
	}

	T& At(size_t index)
	{
		if (index < front.size())
		{
			return front[index];
		}
		index -= front.size();
		if (index < back.size())
		{
			return back[index];
		}
		//throw out_of_range("Out of range.");
	}

	const T& At(size_t index) const
	{
		if (index < front.size())
		{
			return front[index];
		}
		index -= front.size();
		if (index < back.size())
		{
			return back[index];
		}
		throw out_of_range("Out of range.");
	}

	T& Front() { return front.at(0); }
	const T& Front() const { return front.at(0); }

	T& Back() { return back.at(back.size() - 1); }
	const T& Back() const { return back.at(back.size() - 1); }

	void PushFront(T value) { front.insert(front.begin(), value); }
	void PushBack(T value) { back.push_back(value); }
private:
	vector<T> front, back;
};