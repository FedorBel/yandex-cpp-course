#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

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

        ClientStamped client;
        client.time = book_event.time;
        client.client_id = book_event.client_id;
        AddClient(hotel_name, client);

        RoomsStamped rooms;
        rooms.time = book_event.time;
        rooms.room_count = book_event.room_count;
        AddRooms(hotel_name, rooms);
    }

    void Clients(const Events::Clients &client_event)
    {
    }

    void Rooms(const Events::Rooms &rooms_event)
    {
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
        int64_t time;
    };

    int64_t current_time_;
    unordered_map<string, list<ClientStamped>> clients_map_;
    unordered_map<string, list<RoomsStamped>> rooms_map_;

private:
    void AddClient(const string &hotel_name, ClientStamped &client)
    {
        auto &clients = clients_map_[hotel_name];
        clients.push_front(client);
        while (!clients.empty())
        {
            if (clients.back().time <= (current_time_ - 86400))
            {
                clients.pop_back();
            }
            else
            {
                break;
            }
        }
    }
    void AddRooms(const string &hotel_name, RoomsStamped &rooms)
    {
        auto &rooms_count = rooms_map_[hotel_name];
        rooms_count.push_front(rooms);
        while (!rooms_count.empty())
        {
            if (rooms_count.back().time <= (current_time_ - 86400))
            {
                rooms_count.pop_back();
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
        }
        else if (event == "CLIENTS")
        {
            Events::Clients clients_event;
            cin >> clients_event;
        }
        else if (event == "ROOMS")
        {
            Events::Rooms rooms_event;
            cin >> rooms_event;
        }
    }

    return 0;
}