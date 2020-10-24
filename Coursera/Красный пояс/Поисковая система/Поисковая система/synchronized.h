#pragma once

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

// Реализуйте шаблон Synchronized<T>.
// Метод GetAccess должен возвращать структуру, в которой есть поле T& value.
template <typename T>
class Synchronized {
public:

	using MutexType = std::mutex;
	using ReadLock = std::unique_lock<MutexType>;
	using WriteLock = std::unique_lock<MutexType>;

	Synchronized& operator=(Synchronized&& a)
	{
		if (this != &a)
		{
			WriteLock lhs_lk(m, std::defer_lock);
			WriteLock rhs_lk(a.m, std::defer_lock);
			std::lock(lhs_lk, rhs_lk);
			value = std::move(a.value);
		}
		return *this;
	}

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
