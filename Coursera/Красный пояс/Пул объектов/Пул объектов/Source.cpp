#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate()
	{
		if (deallocated_obj.empty())
		{
			T* new_obj = new T;
			allocated_obj.insert(new_obj);
			return new_obj;
		}
		else
		{
			T* new_obj = deallocated_obj.front();
			allocated_obj.insert(new_obj);
			deallocated_obj.pop();
			return new_obj;
		}
	}

	T* TryAllocate()
	{
		if (deallocated_obj.empty())
		{			
			return nullptr;
		}
		else
		{
			T* new_obj = deallocated_obj.front();
			allocated_obj.insert(new_obj);
			deallocated_obj.pop();
			return new_obj;
		}
	}

	void Deallocate(T* object)
	{
		auto pfind = allocated_obj.find(object);
		if (pfind == allocated_obj.end())
		{
			throw invalid_argument("");
		}
		else
		{
			deallocated_obj.push(object);
			allocated_obj.erase(object);
		}
	}

	~ObjectPool()
	{
		for (auto& i : allocated_obj)
		{
			delete i;
		}

		allocated_obj.clear();

		while (!deallocated_obj.empty())
		{
			delete deallocated_obj.front();
			deallocated_obj.pop();
		}
	}

private:
	set<T*> allocated_obj;
	queue<T*> deallocated_obj;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}