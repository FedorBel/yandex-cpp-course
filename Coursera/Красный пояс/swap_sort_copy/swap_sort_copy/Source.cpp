#include"test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	int range_length = range_end - range_begin;
	if (range_length < 2) {
		return;
	}

	// 2. Создаем вектор, содержащий все элементы текущего диапазона
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	// 3. Разбиваем вектор на две равные части
	auto mid = elements.begin() + range_length / 2;

	// 4. Вызываем функцию MergeSort от каждой половины вектора
	MergeSort(elements.begin(), mid);
	MergeSort(mid, elements.end());

	// 5. С помощью алгоритма merge сливаем отсортированные половины
	// в исходный диапазон
	// merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
	merge(elements.begin(), mid, mid, elements.end(), range_begin, [](const auto& lhs, const auto& rhs) {
		return *lhs < *rhs; });
}

template <typename T>
void Swap(T* first, T* second)
{
	T tmp = *first;
	*first = *second;
	*second = tmp;
}

template <typename T>
void SortPointers(vector<T*>& pointers)
{
	MergeSort(begin(pointers), end(pointers));
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination)
{
	T* beg = destination;
	T* tmp = new T[count];
	/*
	if (destination < (source + count) && destination >= source)
	{
		std::reverse_copy(source, source + count, tmp);
		
		for (auto it = source; it != beg; ++it)
		{
			*destination = *source;
			++destination;
		}
		
		copy(tmp, tmp + count, --destination);		
	}
	else if (destination < source && destination + count > source)
	{
		std::reverse_copy(source, source + count, tmp);
		
		for (auto it = source + count; it != beg; --it)
		{
			*destination = *source;
			--destination;
		}
		
		copy(tmp, tmp + count, ++destination);
	}
	else
	{
		std::reverse_copy(source, source + count, destination);
	}	
	destination = tmp;
	*/
	std::reverse_copy(source, source + count, tmp);
	copy(tmp, tmp + count, destination);
	//std::reverse_copy(source, source + count, destination);
	delete[] tmp;
}

void TestSwap() {
	int a = 1;
	int b = 2;
	Swap(&a, &b);
	ASSERT_EQUAL(a, 2);
	ASSERT_EQUAL(b, 1);

	string h = "world";
	string w = "hello";
	Swap(&h, &w);
	ASSERT_EQUAL(h, "hello");
	ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
	int one = 1;
	int two = 2;
	int three = 3;

	vector<int*> pointers;
	pointers.push_back(&two);
	pointers.push_back(&three);
	pointers.push_back(&one);

	SortPointers(pointers);

	ASSERT_EQUAL(pointers.size(), 3u);
	ASSERT_EQUAL(*pointers[0], 1);
	ASSERT_EQUAL(*pointers[1], 2);
	ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
	const size_t count = 7;

	int* source = new int[count];
	int* dest = new int[count];

	for (size_t i = 0; i < count; ++i) {
		source[i] = i + 1;
	}
	ReversedCopy(source, count, dest);
	//vector<int> res(dest, dest + count);
	const vector<int> expected1 = { 7, 6, 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

	// Области памяти могут перекрываться
	ReversedCopy(source, count - 1, source + 1);
	//vector<int> res2(source, source + count);
	const vector<int> expected2 = { 1, 6, 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(vector<int>(source, source + count), expected2);

	delete[] dest;
	delete[] source;
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSwap);
	RUN_TEST(tr, TestSortPointers);
	RUN_TEST(tr, TestReverseCopy);
	return 0;
}