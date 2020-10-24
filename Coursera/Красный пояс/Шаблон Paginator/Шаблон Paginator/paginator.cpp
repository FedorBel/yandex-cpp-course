#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator f, Iterator l)
		: first(f), last(l)
	{
		v.assign(first, last);
	}

	Iterator begin() { return first; }
	Iterator begin() const { return first; }

	Iterator end() { return last; }
	Iterator end() const { return last; }

	size_t size() const { return last - first; }
private:
	Iterator first, last;
	vector<typename Iterator::value_type> v;
};

template <typename Iterator>
auto Head(Iterator& begin, Iterator& end, size_t top)
{
	size_t size = end - begin;
	return IteratorRange{
		begin, next(begin, min(top, size))
	};
}

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator end, size_t page_size)
	{
		size_t size = ceil((end - begin) / static_cast<float>(page_size));

		for (size_t i = 0; i < size; i++)
		{
			auto head = Head(begin, end, page_size);
			pages.push_back({ head.begin(), head.end() });
			begin = pages[i].end();
		}
	}

	auto begin() { return pages.begin(); }
	auto begin() const { return pages.begin(); }

	auto end() { return pages.end(); }
	auto end() const { return pages.end(); }

	size_t size() const { return pages.size(); }

private:	
	vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}