#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cstdint>

using namespace std;

struct BookRoomQuerry
{
	int64_t time;
	int32_t client_id;
	string hotel_name;
	int32_t  room_count;
};

istream& operator>>(istream& is, BookRoomQuerry& query)
{
	is >> query.time >> query.hotel_name >> query.client_id >> query.room_count;

	return is;
}

class HotelManager {
public:
	void Book(const BookRoomQuerry& query)
	{		
		Adjust(query.time);
		clients_[query.hotel_name][query.client_id]++;				
		rooms_[query.hotel_name] += query.room_count;
		events.push(query);		
	}

	void getClients_count(const string& hotel_name)
	{
		cout << clients_[hotel_name].size() << "\n";
	}

	void getRooms_count(const string& hotel_name)
	{
		cout << rooms_[hotel_name] << "\n";
	}

private:
	queue<BookRoomQuerry> events;
	map<string, map<int32_t, int32_t>> clients_;
	map<string, int32_t > rooms_;

	void Adjust(int64_t time)
	{
		int64_t time_del = checkTime(time);

		while (!events.empty() && events.front().time <= time_del)
		{
			clients_[events.front().hotel_name][events.front().client_id]--;
			if (clients_[events.front().hotel_name][events.front().client_id] == 0)
			{
				clients_[events.front().hotel_name].erase(events.front().client_id);
			}
			rooms_[events.front().hotel_name] -= events.front().room_count;
			events.pop();
		}
	}

	int64_t checkTime(int64_t time)
	{
		if (time < INT64_MIN + 84600)
		{
			time = INT64_MIN;
		}
		else
		{
			time = time - 86400;
		}

		return time;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelManager hotels;

	uint32_t query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		
		if (query_type == "BOOK") {			
			BookRoomQuerry query;
			cin >> query;
			hotels.Book(query);
		}
		else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			hotels.getClients_count(hotel_name);
		}
		else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			hotels.getRooms_count(hotel_name);
		}
	}

	return 0;
}