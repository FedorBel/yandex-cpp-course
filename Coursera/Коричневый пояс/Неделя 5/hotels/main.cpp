#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <list>
#include <numeric>

using namespace std;

namespace Events
{
    struct Book
    {
        int64_t time;
        string hotel_name;
        int64_t client_id;
        size_t room_count;

        friend istream &operator>>(istream &in, Book &book_event)
        {
            in >> book_event.time;
            in >> book_event.hotel_name;
            in >> book_event.client_id;
            in >> book_event.room_count;
            return in;
        }
    };

    struct Clients
    {
        string hotel_name;

        friend istream &operator>>(istream &in, Clients &clients_event)
        {
            in >> clients_event.hotel_name;
            return in;
        }
    };

    struct Rooms
    {
        string hotel_name;

        friend istream &operator>>(istream &in, Rooms &rooms_event)
        {
            in >> rooms_event.hotel_name;
            return in;
        }
    };
}

class HotelManager
{
public:
    void Book(const Events::Book &book_event)
    {
        current_time_ = book_event.time;
        const auto &hotel_name = book_event.hotel_name;
        book_events_.push_front(book_event);

        clients_map_[hotel_name][book_event.client_id] += book_event.room_count;
        rooms_map_[hotel_name] += book_event.room_count;
        Clear();
    }

    size_t Clients(const Events::Clients &client_event)
    {
        auto &hotel_name = client_event.hotel_name;
        return clients_map_[hotel_name].size();
    }

    size_t Rooms(const Events::Rooms &rooms_event)
    {
        return rooms_map_[rooms_event.hotel_name];
    }

private:
    struct ClientStamped
    {
        int64_t client_id;
        int64_t time;
    };

    struct RoomsStamped
    {
        size_t room_count;
        int64_t client_id;
        int64_t time;
    };

    int64_t current_time_;
    list<Events::Book> book_events_;
    unordered_map<string, unordered_map<int64_t, int>> clients_map_;
    unordered_map<string, size_t> rooms_map_;

private:
    void Clear()
    {
        while (!book_events_.empty())
        {
            if (book_events_.back().time <= (current_time_ - 86400))
            {
                auto &book_event = book_events_.back();

                auto &client_room_count = clients_map_[book_event.hotel_name][book_event.client_id];
                client_room_count -= book_event.room_count;
                if (client_room_count == 0)
                {
                    clients_map_[book_event.hotel_name].erase(book_event.client_id);
                }
                rooms_map_[book_event.hotel_name] -= book_event.room_count;
                book_events_.pop_back();
            }
            else
            {
                break;
            }
        }
    }
};

int main()
{
    size_t Q;
    cin >> Q;
    HotelManager manager;
    for (size_t i = 0; i < Q; i++)
    {
        string event;
        cin >> event;
        if (event == "BOOK")
        {
            Events::Book book_event;
            cin >> book_event;
            manager.Book(book_event);
        }
        else if (event == "CLIENTS")
        {
            Events::Clients clients_event;
            cin >> clients_event;
            cout << manager.Clients(clients_event) << "\n";
        }
        else if (event == "ROOMS")
        {
            Events::Rooms rooms_event;
            cin >> rooms_event;
            cout << manager.Rooms(rooms_event) << "\n";
        }
    }

    return 0;
}