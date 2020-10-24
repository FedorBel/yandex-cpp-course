#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <mutex>
#include <map>
using namespace std;

template <typename T>
T Abs(T x) {
	return x < 0 ? -x : x;
}

template <typename K, typename V>
class ConcurrentMapStr {
public:
	static_assert(
		is_convertible_v<K, string>,
		"ConcurrentMapStr supports only string keys"
		);

	struct Access {
		lock_guard<mutex> guard;
		V& ref_to_value;		

		Access(const K& key, pair<mutex, map<K, V>>& bucket_content)
			: guard(bucket_content.first)
			, ref_to_value(bucket_content.second[key])
		{			
		}
	};

	explicit ConcurrentMapStr(size_t bucket_count = 10)
		: data(bucket_count)
	{
	}

	Access operator[](const K& key) {
		auto& bucket = data[key.size() % data.size()];
		return { key, bucket };
	}

	map<K, V> BuildOrdinaryMap() {
		map<K, V> result;
		for (auto&[mtx, mapping] : data) {
			lock_guard<mutex> g(mtx);
			result.insert(begin(mapping), end(mapping));
		}
		return result;
	}

private:
	vector<pair<mutex, map<K, V>>> data;
};
