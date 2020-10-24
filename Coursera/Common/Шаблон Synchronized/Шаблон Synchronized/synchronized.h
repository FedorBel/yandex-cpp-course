#pragma once

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

// ���������� ������ Synchronized<T>.
// ����� GetAccess ������ ���������� ���������, � ������� ���� ���� T& value.
template <typename T>
class Synchronized {
public:
	explicit Synchronized(T initial = T())
		: value(move(initial))
	{
	}

	struct Access {
		T& ref_to_value;
		lock_guard<mutex> guard;
	};

	Access GetAccess()
	{
		return { value, lock_guard(m) };
	}
private:
	T value;
	mutex m;
};
