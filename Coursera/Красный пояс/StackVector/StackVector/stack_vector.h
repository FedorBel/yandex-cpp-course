//#pragma once

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0)
	{
		if (a_size > N)
		{
			throw invalid_argument("size > capacity");
		}
		else
		{			
			size = a_size;
		}
	}

	T& operator[](size_t index)
	{
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

	const T* begin() const
	{
		return data;
	}

	const T* end() const
	{
		return data + size;
	}

	size_t Size() const { return size; }
	size_t Capacity() const { return capacity; }

	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			throw overflow_error("size == capasity");
		}
		else
		{
			data[size] = value;
			size++;
		}
	}

	T PopBack()
	{
		if (size == 0)
		{
			throw underflow_error("size == 0");
		}
		else
		{
			T result = data[size - 1];
			size--;
			return result;
		}
	}

private:
	size_t size = 0;
	size_t capacity = N;

	T data[N];
};
