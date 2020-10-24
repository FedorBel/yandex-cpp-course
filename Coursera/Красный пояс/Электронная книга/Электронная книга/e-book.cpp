#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <set>

using namespace std;

class ReadingManager {
public:
	void Read(int user_id, int page_count) {
		try
		{
			int page = user_page_counts_.at(user_id);
			user_positions_.at(page).erase(user_id);
			if (user_positions_.at(page).empty())
			{
				user_positions_.erase(page);
			}
		}
		catch (const std::exception&)
		{

		}
		user_page_counts_[user_id] = page_count;
		user_positions_[page_count].insert(user_id);
	}

	double Cheer(int user_id) const {
		if (user_page_counts_.count(user_id) == 0) {
			return 0;
		}
		const int user_count = GetUserCount();
		if (user_count == 1) {
			return 1;
		}

		int page = user_page_counts_.at(user_id);
		auto it = user_positions_.upper_bound(page);
		map<int, set<int>> less_users{ user_positions_.begin(), prev(it) };
		int less_user_count = 0;
		for (const auto& user : less_users)
		{
			less_user_count += user.second.size();
		}

		// По умолчанию деление целочисленное, поэтому
		// нужно привести числитель к типу double.
		// Простой способ сделать это — умножить его на 1.0.
		return (less_user_count) * 1.0 / (user_count - 1);
	}

private:
	map<int, int> user_page_counts_;
	map<int, set<int>> user_positions_;
	//map<int, int> sorted_users_;

	int GetUserCount() const {
		return user_page_counts_.size();
	}
};


int main() {
	// Для ускорения чтения данных отключается синхронизация
	// cin и cout с stdio,
	// а также выполняется отвязка cin от cout
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		}
		else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}