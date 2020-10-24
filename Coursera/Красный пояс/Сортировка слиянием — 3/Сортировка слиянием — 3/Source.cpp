#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t size = (range_end - range_begin);

	if (size < 2)
	{
		return;
	}

	vector<typename RandomIt::value_type> full_vec
	(
		make_move_iterator(range_begin),
		make_move_iterator(range_end)
	);

	/*
	vector<typename RandomIt::value_type> first_vec
	(
		make_move_iterator(range_begin),
		make_move_iterator(range_begin + size/3)
	);
	vector<typename RandomIt::value_type> middle_vec
	(
		make_move_iterator(range_begin + size / 3),
		make_move_iterator(range_begin + size *2 / 3)
	);
	vector<typename RandomIt::value_type> last_vec
	(
		make_move_iterator(range_begin + size * 2 / 3),
		make_move_iterator(range_end)
	); */

	MergeSort(
		range_begin,
		range_begin + size / 3);

	MergeSort(
		range_begin + size / 3,
		range_begin + size * 2 / 3);

	MergeSort(
		range_begin + size * 2 / 3,
		range_end);

	vector<typename RandomIt::value_type> tmp_vec;
	
	std::merge(
		make_move_iterator(range_begin),
		make_move_iterator(range_begin + size / 3),
		make_move_iterator(range_begin + size / 3),
		make_move_iterator(range_begin + size * 2 / 3),
		back_inserter(tmp_vec));

	std::merge(
		make_move_iterator(tmp_vec.begin()),
		make_move_iterator(tmp_vec.end()),
		make_move_iterator(range_begin + size * 2 / 3),
		make_move_iterator(range_end),		
		range_begin);

}

void TestIntVector() {
	vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
