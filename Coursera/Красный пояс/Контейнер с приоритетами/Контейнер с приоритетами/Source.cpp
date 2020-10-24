#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
class PriorityCollection {
public:
	using Id = uint64_t;
	using private_Id = typename list<T>::iterator;
	static uint64_t id_count;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object)
	{
		elements.push_back(move(object));

		private_Id private_id = prev(elements.end());
		Id id = id_count++;

		id_to_private_id[id] = private_id;
		priority_to_id[0].insert(id);
		id_to_priority[id] = 0;

		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
		IdOutputIt ids_begin)
	{
		for (auto& it = range_begin; it != range_end; ++it)
		{
			*ids_begin++ = Add(move(*range_begin));
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const
	{
		return id_to_private_id.find(id) != id_to_private_id.end();
	}

	// Получить объект по идентификатору
	const T& Get(Id id) const
	{
		return *(id_to_private_id.at(id));
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id)
	{
		auto priority = id_to_priority[id]++;
		priority_to_id[priority].erase(id);
		if (priority_to_id[priority].empty())
			priority_to_id.erase(priority);
		priority_to_id[++priority].insert(id);
	}

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T&, int> GetMax() const
	{
		auto prior_it = prev(priority_to_id.end());

		int priority = prior_it->first;

		Id max_el_id = *(prev(prior_it->second.end()));

		private_Id priv_id = id_to_private_id.at(max_el_id);		
		
		return { *priv_id , priority };
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax()
	{
		auto prior_it = prev(priority_to_id.end());

		int priority = prior_it->first;

		Id max_el_id = *(prev(prior_it->second.end()));		

		private_Id priv_id = id_to_private_id[max_el_id];
		T result = move(*priv_id);

		elements.erase(priv_id);
		prior_it->second.erase(prev(prior_it->second.end()));
		if (prior_it->second.empty())
			priority_to_id.erase(prior_it);
		id_to_private_id.erase(max_el_id);
		id_to_priority.erase(max_el_id);
		return { move(result) , priority };
	}

private:
	map<int, set<Id>> priority_to_id;
	map<Id, private_Id> id_to_private_id;
	map<Id, int> id_to_priority;
	list<T> elements;	
};

template <typename T>
uint64_t PriorityCollection<T>::id_count = 0;


class StringNonCopyable : public string {
public:
	using string::string;  // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);

	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
