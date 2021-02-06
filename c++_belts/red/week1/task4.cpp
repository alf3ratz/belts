#include <iostream>
#include <ostream>
#include <vector>
#include <memory>
#include <sstream>
#include "airline_ticket.h"
#include "test_runner.h"
#include <map>


using namespace std;
//struct Date {
//    int year, month, day;
//};
//
//struct Time {
//    int hours, minutes;
//};
//
//struct AirlineTicket {
//    string from;
//    string to;
//    string airline;
//    Date departure_date;
//    Time departure_time;
//    Date arrival_date;
//    Time arrival_time;
//    int price;
//};
#define SORT_BY(field)[](AirlineTicket& left, AirlineTicket& right){return left.field<right.field;}

istream &operator>>(istream &is, Date &date) {
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;
    return is;
}

istream &operator>>(istream &is, Time &time) {
    is >> time.hours;
    is.ignore(1);
    is >> time.minutes;

    return is;
}

#define UPDATE_FIELD(ticket, field, values)    {            \
        if (values.find(#field) != values.end()) {          \
        istringstream is(values.find(#field)->second);      \
        is >> ticket.field;                                 \
                                                            \
        }                                                   \
}

bool operator<(const Date &left, const Date &right) {
    auto a = tie(left.day, left.month, left.year);
    auto b = tie(right.day, right.month, right.year);
    return a < b;
}

bool operator==(const Date &left, const Date &right) {
    auto a = tie(left.year, left.month, left.day);
    auto b = tie(right.year, right.month, right.day);
    return a == b;
}

bool operator<(const Time &left, const Time &right) {
    auto a = tie(left.hours, left.minutes);
    auto b = tie(right.hours, right.minutes);
    return a < b;
}

bool operator==(const Time &left, const Time &right) {
    auto a = tie(left.hours, left.minutes);
    auto b = tie(right.hours, right.minutes);
    return a == b;
}

ostream &operator<<(ostream &os, const Date &date) {
    os << date.day << ":" << date.month << ":" << date.year << "\n";
    return os;
}

ostream &operator<<(ostream &os, const Time &time) {
    os << time.hours << ":" << time.minutes << "\n";
    return os;
}

//void TestUpdate() {
//    AirlineTicket t;
//    t.price = 0;
//
//    const map<string, string> updates1 = {
//            {"departure_date", "2018-2-28"},
//            {"departure_time", "17:40"},
//    };
//    UPDATE_FIELD(t, departure_date, updates1);
//    UPDATE_FIELD(t, departure_time, updates1);
//    UPDATE_FIELD(t, price, updates1);
//
//    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//    ASSERT_EQUAL(t.price, 0);
//
//    const map<string, string> updates2 = {
//            {"price", "12550"},
//            {"arrival_time", "20:33"},
//    };
//    UPDATE_FIELD(t, departure_date, updates2);
//    UPDATE_FIELD(t, departure_time, updates2);
//    UPDATE_FIELD(t, arrival_time, updates2);
//    UPDATE_FIELD(t, price, updates2);
//
//    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//    ASSERT_EQUAL(t.price, 12550);
//    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
//}


int main() {

}
