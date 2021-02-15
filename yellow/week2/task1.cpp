#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string command;
    is >> command;
    int count;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        cin >> count;
        q.stops.resize(count);
        for (string& stop : q.stops) {
            cin >> stop;
        }
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    map<string, vector<string>> stops_for_buses;
    string stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stops_for_buses.count(r.stop) == 0) {
        os << "No stop";
    } else {
        for (const string& bus : r.stops_for_buses.at(r.stop)) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    map<string, vector<string>> stops_for_buses;
    map<string, vector<string>> buses_for_stops;
    string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.buses_for_stops.count(r.bus) == 0) {
        os << "No bus";
    } else {
        int i = 0;
        for (const string& stop : r.buses_for_stops.at(r.bus)) {
            os << "Stop " << stop << ": ";
            if (r.stops_for_buses.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (const string& bus : r.stops_for_buses.at(stop)) {
                    if (r.bus != bus) {
                        os << bus << " ";
                    }
                }
            }
            if (i < (r.stops_for_buses.size() - 1)){
                os << endl;
                i++;
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()) {
        os << "No buses";
    } else {
        int i = 0;
        for (const auto& bus : r.buses) {
            os << "Bus " << bus.first << ": ";
            for (const string& stop : bus.second) {
                os << stop << " ";
            }
            if (i < r.buses.size()-1){
                os << endl;
                i++;
            }
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        for (const string& stop : stops) {
            stops_for_buses[stop].push_back(bus);
        }
        buses_for_stops[bus] = stops;
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        return {stops_for_buses,stop};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        return {stops_for_buses,buses_for_stops,bus};
    }

    AllBusesResponse GetAllBuses() const {
        return {buses_for_stops};
    }
private:
    map<string, vector<string>> stops_for_buses;
    map<string, vector<string>> buses_for_stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}