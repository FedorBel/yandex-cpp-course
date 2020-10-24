#include "test_runner.h"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <memory>

using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;

	bool operator==(const Record& other) const
	{
		return
			id == other.id &&
			title == other.title &&
			user == other.user &&
			timestamp == other.timestamp &&
			karma == other.karma;
	}
};

struct RecordHasher {
	size_t operator() (const Record& r) const
	{
		const size_t coef = 19;

		const hash<int> ihash;
		const hash<string> shash;

		return (
			coef * coef * coef * coef * shash(r.id) +
			coef * coef * coef * shash(r.title) +
			coef * coef * shash(r.user) +
			coef * ihash(r.timestamp) +
			ihash(r.karma)
			);
	}
};

struct SecondaryIndexInfo
{
	multimap<int, Record&>::iterator timestamp_it;
	multimap<int, Record&>::iterator karma_it;
	multimap<string, Record&>::iterator user_it;
};

// Реализуйте этот класс
class Database {
public:
	bool Put(const Record& record)
	{
		/*auto it = records_.find(record.id);
		if (it != records_.end()) 
		{
			return false;
		}*/
		auto insert_res = records_.insert({ record.id , {} });
		if (!insert_res.second)
		{
			return false;
		}
		// records_list_.push_back({ record,  {} });
		auto record_it = records_list_.insert(records_list_.end(), { record,  {} });
		insert_res.first->second = record_it;

		SecondaryIndexInfo& record_info = record_it->second;
		//shared_ptr<Record> p_record = make_shared<Record>(record_it->first);
		record_info.timestamp_it = range_by_timestamp_.insert({ record.timestamp, record_it->first });
		record_info.karma_it = range_by_karma_.insert({ record.karma, record_it->first });
		record_info.user_it = range_by_user_.insert({ record.user, record_it->first });
		// records_list_.push_back({ record,  move(record_info) });

		// auto record_it = prev(records_list_.end());
		// records_[record.id] = record_it;
				
		return true;
	}

	const Record* GetById(const string& id) const
	{
		auto it = records_.find(id);
		if (it == records_.end())
		{
			return nullptr;
		}
		return &(it->second->first);
	}

	bool Erase(const string& id)
	{
		auto it = records_.find(id);
		if (it == records_.end())
		{
			return false;
		}
		// auto record_info_it = secondary_index_info_.find(id);
		auto& record_info = it->second->second;
		range_by_timestamp_.erase(record_info.timestamp_it);
		range_by_karma_.erase(record_info.karma_it);
		range_by_user_.erase(record_info.user_it);
		// secondary_index_info_.erase(record_info_it);
		records_list_.erase(it->second);
		records_.erase(it);
		return true;
	}

	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const
	{
		auto end = range_by_timestamp_.upper_bound(high);
		for (auto it = range_by_timestamp_.lower_bound(low); it != end; ++it)
		{
			if (!callback(it->second))
			{
				return;
			}
		}
	}

	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const
	{
		auto end = range_by_karma_.upper_bound(high);
		for (auto it = range_by_karma_.lower_bound(low); it != end; ++it)
		{
			if (!callback(it->second))
			{
				return;
			}
		}
	}

	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const
	{
		auto end = range_by_user_.upper_bound(user);
		for (auto it = range_by_user_.lower_bound(user); it != end; ++it)
		{
			if (!callback(it->second))
			{
				return;
			}
		}
	}

private:
	unordered_map<string, list<pair<Record, SecondaryIndexInfo>>::iterator> records_;	
	list<pair<Record, SecondaryIndexInfo>> records_list_;
	multimap<int, Record&> range_by_timestamp_;
	multimap<int, Record&> range_by_karma_;
	multimap<string, Record&> range_by_user_;
	// unordered_map<string, SecondaryIndexInfo> secondary_index_info_;	
};

void TestRangeBoundaries() {
	const int good_karma = 1000;
	const int bad_karma = -10;

	Database db;
	db.Put({ "id1", "Hello there", "master", 1536107260, good_karma });
	db.Put({ "id2", "O>>-<", "general2", 1536107260, bad_karma });

	int count = 0;
	db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestSameUser() {
	Database db;
	db.Put({ "id1", "Don't sell", "master", 1536107260, 1000 });
	db.Put({ "id2", "Rethink life", "master", 1536107260, 2000 });

	int count = 0;
	db.AllByUser("master", [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestReplacement() {
	const string final_body = "Feeling sad";

	Database db;
	db.Put({ "id", "Have a hand", "not-master", 1536107260, 10 });
	db.Erase("id");
	db.Put({ "id", final_body, "not-master", 1536107260, -10 });

	auto record = db.GetById("id");
	ASSERT(record != nullptr);
	ASSERT_EQUAL(final_body, record->title);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestRangeBoundaries);
	RUN_TEST(tr, TestSameUser);
	RUN_TEST(tr, TestReplacement);
	return 0;
}
