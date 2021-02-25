
#include "database.h"

void Database::Add(const Date &date, const string &event) {
    if (!event_to_date.count(event) || !event_to_date[event].count(date)) {
        date_to_event[date].push_back(event);
        event_to_date[event].insert(date);
    }
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date & date, const string & event)>& pred) const {
    vector<pair<Date, string>> entries;

    for (const auto &item: date_to_event) {
        for (const auto &event: item.second) {
            if (pred(item.first, event)) {
                entries.emplace_back(pair<Date, string>(item.first, event));
            }
        }
    }

    return entries;
}

int Database::RemoveIf(const function<bool(const Date & date, const string &event)>& pred) {
    int deleted= 0;
    vector<string> helper;

    for (auto i = date_to_event.begin(); i != date_to_event.end();){
        for(const auto& event: i->second){
            if (pred(i->first, event)){
                deleted++;

                event_to_date[event].erase(i->first);

                if (event_to_date[event].empty()) {
                    event_to_date.erase(event);
                }
            }
        }

        auto start = remove_if(i->second.begin(), i->second.end(),
                               [&](const string& event){return pred(i->first, event);});

        i->second.erase(start, i->second.end());

        if (i->second.empty()){
            i = date_to_event.erase(i);
        } else{
            i++;
        }
    }

    return deleted;
}

pair<Date, string> Database::Last(const Date &date) const {
    auto iter = date_to_event.upper_bound(date);

    if (iter != date_to_event.begin()) {
        iter = prev(iter);
        return make_pair(iter->first, iter->second.back());
    } else {
        throw invalid_argument("There is no last element in database :(");
    }
}

void Database::Print(ostream& os) const {
    for(const auto& [key, value]: date_to_event){
        for(const auto& event: value){
            os << key << ' ' << event << endl;
        }
    }
}

ostream &operator<<(ostream &os, const pair<Date, string>& pair) {
    os << pair.first << ' ' << pair.second;
    return os;
}

