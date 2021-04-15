#include "test_runner.h"

#include <cstddef> // нужно для nullptr_t

#include <algorithm>

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr
{
private:
	T *ptr_raw_ = nullptr;

public:
	UniquePtr()
	{
	}

	UniquePtr(T *ptr)
	{
		Reset(ptr);
	}

	UniquePtr(const UniquePtr &) = delete;

	UniquePtr(UniquePtr &&other)
	{
		Reset(other.Get());
		other.ptr_raw_ = nullptr;
	}

	UniquePtr &operator=(const UniquePtr &) = delete;

	UniquePtr &operator=(nullptr_t null_ptr)
	{
		Reset(null_ptr);
		return *this;
	}

	UniquePtr &operator=(UniquePtr &&other)
	{
		Reset(other.Get());
		other.ptr_raw_ = nullptr;
		return *this;
	}

	~UniquePtr()
	{
		if (ptr_raw_)
		{
			delete ptr_raw_;
		}
	}

	T &operator*() const
	{
		return *ptr_raw_;
	}

	T *operator->() const
	{
		return ptr_raw_;
	}

	T *Release()
	{
		T *res = ptr_raw_;
		ptr_raw_ = nullptr;
		return res;
	}

	void Reset(T *ptr)
	{
		if (ptr_raw_)
		{
			delete ptr_raw_;
		}
		ptr_raw_ = ptr;
	}

	void Swap(UniquePtr &other)
	{
		std::swap(this->ptr_raw_, other.ptr_raw_);
	}

	T *Get() const
	{
		return ptr_raw_;
	}
};

struct Item
{
	static int counter;
	int value;
	Item(int v = 0) : value(v)
	{
		++counter;
	}
	Item(const Item &other) : value(other.value)
	{
		++counter;
	}
	~Item()
	{
		--counter;
	}
};

int Item::counter = 0;

void TestLifetime()
{
	Item::counter = 0;
	{
		UniquePtr<Item> ptr(new Item);
		ASSERT_EQUAL(Item::counter, 1);

		ptr.Reset(new Item);
		ASSERT_EQUAL(Item::counter, 1);
	}
	ASSERT_EQUAL(Item::counter, 0);

	{
		UniquePtr<Item> ptr(new Item);
		ASSERT_EQUAL(Item::counter, 1);

		auto rawPtr = ptr.Release();
		ASSERT_EQUAL(Item::counter, 1);

		delete rawPtr;
		ASSERT_EQUAL(Item::counter, 0);
	}
	ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters()
{
	UniquePtr<Item> ptr(new Item(42));
	ASSERT_EQUAL(ptr.Get()->value, 42);
	ASSERT_EQUAL((*ptr).value, 42);
	ASSERT_EQUAL(ptr->value, 42);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestLifetime);
	RUN_TEST(tr, TestGetters);
}
