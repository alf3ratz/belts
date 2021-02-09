#include <iostream>
#include <vector>

using namespace std;


int main() {
    int Q, count = 0, num;
    string name, temp;
    const vector<int> dayPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<vector<string>> month(dayPerMonth[0], vector<string>(0));
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> temp;
        if (temp == "ADD") {
            cin >> num >> name;
            num--;
            month[num].push_back(name);
//            if (month[num].empty())
//                month[num] = vector<string>{name};
//            else {
//                month[num].insert(end(month[num]), begin(vector<string>{name}), end(vector<string>{name}));
//            }
        } else if (temp == "NEXT") {
            count++;
            if (count == 12)
                count = 0;
            vector<vector<string>> newMonth(dayPerMonth[count]);
            if (newMonth.size() > month.size()) {
                for (int j = 0; j < month.size(); ++j) {
                    newMonth[j] = month[j];
                }
                for (int j = month.size(); j < newMonth.size(); ++j) {
                    newMonth[j] = vector<string>();
                }
            } else {
                for (int j = 0; j < newMonth.size(); ++j) {
                    newMonth[j] = month[j];
                }
                for (int j = newMonth.size(); j < month.size(); ++j) {
                    newMonth[newMonth.size() - 1].insert(end(newMonth[newMonth.size() - 1]), begin(month[j]),
                                                         end(month[j]));
                }
            }
            month = newMonth;
        } else {//DUMP
            cin >> num;
            num--;
            cout << month[num].size() << " ";
            for (int j = 0; j < month[num].size(); ++j) {
                cout << month[num][j] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
