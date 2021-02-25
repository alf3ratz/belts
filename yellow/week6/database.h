#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <map>
#include <set>
#include "date.h"

#pragma once
using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);

    vector<pair<Date, string>> FindIf(const function<bool(const Date &, const string &)>& pred) const;

    int RemoveIf(const function<bool(const Date &, const string &)>& pred);

    pair<Date, string> Last(const Date& date) const;

    void Print(ostream&) const;

private:
    map<Date, vector<string>> date_to_event;
    map<string, set<Date>> event_to_date;
};

ostream &operator<<(ostream &os, const pair<Date, string>& pair);
