#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


class Person {
public:
    string PrintPerson(int year) {
        if (year > years[years.size() - 1]) {
            year = years[years.size() - 1];
        }
        if (identification[year].second.empty()) {
            return identification[year].first + " with unknown last name";
        } else if (identification[year].first.empty()) {
            return identification[year].second + " with unknown first name";
        } else {
            return identification[year].first + " " + identification[year].second + "";
        }
    }

    void ChangeFirstName(int year, const string &first_name) {
        if (identification.count(year) != 0) {
            identification[year].first = first_name;
        } else {
            if (!years.empty()) {
                int num;
                for (auto &i:years) {
                    if (i < year)
                        num = i;
                }
                string old_name = identification[num].first;
                identification[year].first = first_name;
                identification[year].second = identification[num].second;
                for (auto&[key, value]:identification) {
                    if (key > year)
                        if (value.first == old_name || value.first.empty())
                            value.first = first_name;
                }
            } else
                identification[year] = make_pair(first_name, "");
        }
        years.push_back(year);
        sort(begin(years), end(years));
        // добавить факт изменения имени на first_name в год year
    }

    void ChangeLastName(int year, const string &last_name) {
        if (identification.count(year) != 0) {
            identification[year].second = last_name;
        } else {
            if (!years.empty()) {
                int num;
                for (auto &i:years) {
                    if (i < year)
                        num = i;
                }
                string old_surname = identification[num].second;
                identification[year].second = last_name;
                identification[year].first = identification[num].first;
                for (auto&[key, value]:identification) {
                    if (key > year)
                        if (value.second == old_surname || value.second.empty())
                            value.second = last_name;
                }
            } else
                identification[year] = make_pair("", last_name);
        }
        years.push_back(year);
        sort(begin(years), end(years));
        // добавить факт изменения фамилии на last_name в год year
    }

    string GetFullName(int year) {
        if (year < years[0]) {
            return "Incognito";
        } else if (year > years[years.size() - 1]) {
            return PrintPerson(year);
        } else if (identification.count(year) == 0 && year > years[0] && year < years[years.size() - 1]) {
            int num;
            for (auto &i:years) {
                if (i < year)
                    num = i;
            }
            year = num;
        }
        if (identification[year].second.empty()) {
            return identification[year].first + " with unknown last name";
        } else if (identification[year].first.empty()) {
            return identification[year].second + " with unknown first name";
        } else {
            return identification[year].first + " " + identification[year].second + "";
        }
        // получить имя и фамилию по состоянию на конец года year
    }

private:
    map<int, pair<string, string>> identification;
    vector<int> years;
};

int main() {

    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    return 0;
}