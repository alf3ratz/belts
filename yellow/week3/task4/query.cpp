#include <iostream>
#include <string>

#include "query.h"

using namespace std;
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