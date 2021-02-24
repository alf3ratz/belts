
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "set"
#include "map"
#include "string"

using namespace std;


// Возвращает пустую строку, если имя неизвестно
string FindNameByYear(const map<int, string> &names, int year) {
    string name;
    for (const auto &item : names) {
        if (item.first <= year) {
            name = item.second;
        }
    }
    return name;
}

string GetHistory(int year, const map<int, string> &names) {
    vector<string> history_names;
    string current_name = "";

    for (const auto &item : names) {
        if (item.first <= year) {
            if (item.second != current_name) {
                vector<string> v = {item.second};
                history_names.insert(begin(history_names), begin(v), end(v));
                current_name = item.second;
            }
        } else {
            break;
        }
    }

    string res = "";
    for (int i = 1; i < history_names.size(); ++i) {
        if (res.size() == 0) {
            res += history_names[i];
        } else {
            res += ", " + history_names[i];
        }
    }
    return res;
}

class Person {
public:
    Person(const string& name, const string& surname, int year):birth(year){
        first_names[year] = name;
        last_names[year] = surname;
    }
    void ChangeFirstName(int year, const string &first_name) {
        if (year >=birth) {
            first_names[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string &last_name) {
        if (year >=birth) {
            last_names[year] = last_name;
        }
    }

    string GetFullName(int year)const {
        if (year < birth) {
            return "No person";
        }
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        } else if (first_name.empty()) {
            return last_name + " with unknown first name";
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";
        } else {
            return first_name + " " + last_name;
        }
    }

    string GetFullNameWithHistory(int year)const {
        if (year < birth) {
            return "No person";
        }
        // получить все имена и фамилии по состоянию на конец года year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);
        const string history_first_name = GetHistory(year, first_names);
        const string history_last_name = GetHistory(year, last_names);
        string res = first_name + " (" + history_first_name + ")" + " " + last_name + " (" + history_last_name + ")";

        if (first_name.size() == 0 && last_name.size() == 0) {
            res = "Incognito";
            return res;
        } else if (first_name.size() == 0) {
            if (history_last_name.size() == 0) {
                res = last_name + " with unknown first name";
                return res;
            } else {
                res = last_name + " (" + history_last_name + ")" + " with unknown first name";
                return res;
            }
        } else if (last_name.size() == 0) {
            if (history_first_name.size() == 0) {
                res = first_name + " with unknown last name";
                return res;
            } else {
                res = first_name + " (" + history_first_name + ")" + " with unknown last name";
                return res;
            }
        } else if (history_first_name.size() == 0 && history_last_name.size() == 0) {
            res = first_name + " " + last_name;
            return res;
        } else if (history_first_name.size() == 0) {
            res = first_name + " " + last_name + " (" + history_last_name + ")" ;
            return res;
        } else if (history_last_name.size() == 0) {
            res = first_name + " (" + history_first_name + ") " + last_name;
            return res;
        }
        return res;
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
    set<pair<int, string>> history_first_names;
    set<pair<int, string>> history_last_names;
    const int birth;
};


int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}



