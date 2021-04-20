#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class ReadingManager
{
public:
    ReadingManager() {}

    void Read(int user_id, int page_count)
    {
        const auto it = user_page_counts_.find(user_id);
        if (it != user_page_counts_.end())
        {
            int old_page = it->second;
            DeleteFromBoard(user_id, old_page);
        }
        InsertToBoard(user_id, page_count);
    }

    double Cheer(int user_id) const
    {
        const auto it = user_page_counts_.find(user_id);
        if (it == user_page_counts_.end())
        {
            return 0;
        }

        if (user_page_counts_.size() == 1)
        {
            return 1;
        }

        int users_less = 0;
        const auto stop_it = leaderboard_.find(it->second);
        for (auto i = leaderboard_.begin(); i != stop_it; ++i)
        {
            users_less += i->second.size();
        }
        int users_count = user_page_counts_.size();
        return (users_less * 1.0) / (users_count - 1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;

    using UserId = int;
    using Page = int;

    unordered_map<UserId, Page> user_page_counts_;
    map<Page, unordered_set<UserId>> leaderboard_;

    void InsertToBoard(int user_id, int new_page)
    {
        user_page_counts_[user_id] = new_page;
        leaderboard_[new_page].insert(user_id);
    }

    void DeleteFromBoard(int user_id, int old_page)
    {
        auto& same_score_users = leaderboard_[old_page];
        same_score_users.erase(user_id);
        if (same_score_users.empty())
        {
            leaderboard_.erase(old_page);
        }
    }
};

int main()
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER")
        {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}