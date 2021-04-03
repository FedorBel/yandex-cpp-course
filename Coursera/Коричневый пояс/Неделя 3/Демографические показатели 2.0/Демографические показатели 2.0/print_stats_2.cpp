#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <set>
#include <map>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

class DemographicInfo
{
public:
private:

};

vector<Person> SortByAge(const vector<Person>& people)
{
	vector<Person> data = people;
	sort(begin(data), end(data), [](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
	});
	return data;
}

vector<Person> SortByIncome(const vector<Person>& people)
{
	vector<Person> data = people;
	sort(begin(data), end(data), [](const Person& lhs, const Person& rhs) {
		return lhs.income > rhs.income;
	});
	return data;
}

string FindMostPopularMaleName(const vector<Person>& people)
{
	string result;
	multiset<string> male_names;
	for (const auto& person : people)
	{
		if (person.is_male)
		{
			male_names.insert(person.name);
		}
	}
	if (!male_names.empty())
	{
		result = *male_names.begin();
		int64_t count = 1;
		for (auto i = male_names.begin(); i != male_names.end();)
		{
			auto same_name_end = male_names.upper_bound(*i);
			auto cur_name_count = std::distance(i, same_name_end);
			if (cur_name_count > count) {
				count = cur_name_count;
				result = *i;
			}
			i = same_name_end;
		}
	}
	return result;
}

string FindMostPopularFemaleName(const vector<Person>& people)
{
	string result;
	multiset<string> female_names;
	for (const auto& person : people)
	{
		if (!person.is_male)
		{
			female_names.insert(person.name);
		}
	}
	if (!female_names.empty())
	{
		result = *female_names.begin();
		int64_t count = 1;
		for (auto i = female_names.begin(); i != female_names.end();)
		{
			auto same_name_end = female_names.upper_bound(*i);
			auto cur_name_count = std::distance(i, same_name_end);
			if (cur_name_count > count) {
				count = cur_name_count;
				result = *i;
			}
			i = same_name_end;
		}
	}
	return result;
}

int main() {
	const vector<Person> people = ReadPeople(cin);
	const vector<Person> age_people = SortByAge(people);
	const vector<Person> income_people = SortByIncome(people);
	const string most_popular_male_name = FindMostPopularMaleName(people);
	const string most_popular_female_name = FindMostPopularFemaleName(people);

	for (string command; cin >> command; ) {
		if (command == "AGE") {
			int adult_age;
			cin >> adult_age;

			auto adult_begin = lower_bound(
				begin(age_people), end(age_people), adult_age, [](const Person& lhs, int age) {
				return lhs.age < age;
			}
			);

			cout << "There are " << std::distance(adult_begin, end(age_people))
				<< " adult people for maturity age " << adult_age << '\n';
		}
		else if (command == "WEALTHY") {
			int count;
			cin >> count;

			auto head = Head(income_people, count);

			int total_income = accumulate(
				head.begin(), head.end(), 0, [](int cur, const Person& p) {
				return p.income + cur;
			}
			);
			cout << "Top-" << count << " people have total income " << total_income << '\n';
		}
		else if (command == "POPULAR_NAME") {
			char gender;
			cin >> gender;
			const auto& most_popular_name = gender == 'M' ? most_popular_male_name : most_popular_female_name;			
			if (most_popular_name.empty()) {
				cout << "No people of gender " << gender << '\n';
			}
			else {
				cout << "Most popular name among people of gender " << gender << " is "
					<< most_popular_name << '\n';
			}			
		}
	}  
}
