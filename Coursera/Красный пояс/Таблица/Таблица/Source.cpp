#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include "test_runner.h"

using namespace std;

template<typename T>
class Table
{
public:
	Table(size_t rows, size_t cols)
	{
		Resize(rows, cols);
	}

	void Resize(size_t rows, size_t cols)
	{		
		elements.resize(rows);
		for (auto& i : elements)
		{
			i.resize(cols);
		}
	}

	vector<T>& operator[](size_t ind)
	{
		return elements[ind];
	}

	const vector<T>& operator[](size_t ind) const
	{
		return elements[ind];
	}
	
	pair<size_t, size_t> Size() const { return { elements.size(), (elements.empty() ? 0 : elements[0].size()) }; }
private:
	vector<vector<T>> elements;	
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}