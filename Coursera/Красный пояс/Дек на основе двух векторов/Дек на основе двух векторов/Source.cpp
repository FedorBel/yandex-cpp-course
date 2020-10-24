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
			return front.at((front.size() - 1) - index);
		}
		else
		{
			index -= front.size();
			return back.at(index);
		}
	}

	const T& operator[](size_t index) const
	{
		if (index < front.size())
		{
			return front.at((front.size() - 1) - index);
		}
		else
		{
			index -= front.size();
			return back.at(index);
		}
	}

	T& At(size_t index)
	{
		if (index < front.size())
		{
			return front.at((front.size() - 1) - index);
		}
		index -= front.size();
		if (index < back.size())
		{			
			return back.at(index);
		}
		throw out_of_range("Out of range.");
	}

	const T& At(size_t index) const
	{
		if (index < front.size())
		{
			return front.at((front.size() - 1) - index);
		}
		index -= front.size();
		if (index < back.size())
		{			
			return back.at(index);
		}
		throw out_of_range("Out of range.");
	}

	T& Front() { if (!front.empty()) return front.back(); else return *(back.begin()); }
	const T& Front() const { if (!front.empty()) return front.back(); else return *(back.begin()); }

	T& Back() { if (!back.empty()) return back.at(back.size() - 1); else return *(front.begin()); }
	const T& Back() const { if (!back.empty()) return back.at(back.size() - 1); else return *(front.begin()); }

	void PushFront(T value) { front.push_back(value); }
	void PushBack(T value) { back.push_back(value); }
private:
	vector<T> front, back;
};

int main()
{
	Deque<int> d;
	cout << d.Size() << endl;
	d.PushBack(1);
	d.PushBack(2);
	d.PushFront(3);
	d.PushFront(4);
	cout << d.Front() << endl;
	cout << d.Back() << endl;
	cout << d.At(0) << endl;
	cout << d.At(3) << endl;
	cout << d.Size() << endl;
	cout << d.Empty() << endl;

	return 0;
}