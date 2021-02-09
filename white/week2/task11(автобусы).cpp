#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


int main() {
    int Q, count;
    cin >> Q;
    string task, name, temp;
    map<string, vector<string>> buses;
    map<string, vector<string>> stops;
    for (int i = 0; i < Q; ++i) {
        cin >> task;
        if (task == "NEW_BUS") {
            cin >> name >> count;
            vector<string> lst;
            for (int j = 0; j < count; ++j) {
                cin >> temp;
                stops[temp].push_back(name);
                lst.emplace_back(temp);
            }
            buses[name] = lst;
        } else if (task == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            if (stops.count(stop) == 0){
                cout << "No stop" << endl;
            } else{
                for (const auto& x: stops[stop]){
                    cout << x << " ";
                }
                cout << "\n";
            }
        } else if (task == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            if (buses.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (const auto &x: buses[bus]) {
                    cout << "Stop " << x << ":";
                    if (stops[x].size() == 1) {
                        cout << " no interchange" << endl;
                    } else {
                        for (const auto &y: stops[x]) {
                            if (y != bus)
                                cout << " " << y;
                        }
                        cout << "\n";
                    }
                }
            }
        } else if (task == "ALL_BUSES") {
            if (buses.size() == 0) {
                cout << "No buses" << endl;
            } else {
                for (const auto&[key, value]: buses) {
                    cout << "Bus " << key << ":";
                    for (const auto &x: value) {
                        cout << " " << x;
                    }
                    cout << "\n";
                }
            }
        }
    }

    return 0;
}