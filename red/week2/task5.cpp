#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include "map"
#include "set"
#include "queue"

using namespace std;


class Booking {
public:
    void Book(int64_t time, string hotel_name, int64_t client_id, int64_t room_count) {
        current_time = time;
        timings.push(make_pair(hotel_name, make_tuple(client_id, room_count, time)));
        hotel_to_rooms[hotel_name] += room_count;
        Adjust(current_time);
        hotel_to_clinets[hotel_name].insert(client_id);
    }

    int Clients(string hotel_name) {
        return hotel_to_clinets[hotel_name].size();
    }

    int Rooms(string hotel_name) {
        Adjust(current_time);
        return hotel_to_rooms[hotel_name];
    }

private:
    void Adjust(int64_t time) {
        while (!timings.empty() && get<2>(timings.front().second) <= time - 86400) {
            string hotel = timings.front().first;
            int64_t client = get<0>(timings.front().second);
            int64_t room_count = get<1>(timings.front().second);
            hotel_to_rooms[hotel] -= room_count;
            hotel_to_clinets[hotel].erase(client);
            timings.pop();
        }
    }


    int64_t current_time;
    map<string, int64_t> hotel_to_rooms;
    map<string, set<int64_t>> hotel_to_clinets;
    queue<pair<string, tuple<int64_t, int64_t, int64_t>>> timings;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Booking manager;

    int64_t query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
            int64_t time, client_id, room_count;
            string hotel_name;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        } else {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << "\n";
        }
    }

    return 0;
}