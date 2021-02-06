#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <tuple>
#include "airline_ticket.h"
#include "test_runner.h"


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

bool operator<(const Date& left, const Date& right){
    auto a = tie(left.day,left.month,left.year);
    auto b = tie(right.day,right.month,right.year);
    return a<b;
}
bool operator==(const Date& left,const Date& right){
    auto a = tie(left.year,left.month,left.day);
    auto b = tie(right.year,right.month,right.day);
    return a==b;
}
bool operator<(const Time& left,const Time& right){
    auto a = tie(left.hours,left.minutes);
    auto b = tie(right.hours,right.minutes);
    return a<b;
}
bool operator==(const Time& left, const Time& right){
    auto a = tie(left.hours,left.minutes);
    auto b = tie(right.hours,right.minutes);
    return a==b;
}

ostream& operator<<(ostream& os,const Date& date){
    os << date.day << ":" << date.month << ":" << date.year << "\n";
    return os;
}

ostream& operator<<(ostream& os,const Time& time){
    os << time.hours << ":" << time.minutes << "\n";
    return os;
}

//void TestSortBy() {
//    vector<AirlineTicket> tixs = {
//            {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
//            {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
//            {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
//            {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
//            {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
//    };
//
//    sort(begin(tixs), end(tixs), SORT_BY(price));
//    ASSERT_EQUAL(tixs.front().price, 1200);
//    ASSERT_EQUAL(tixs.back().price, 9000);
//
//    sort(begin(tixs), end(tixs), SORT_BY(from));
//    ASSERT_EQUAL(tixs.front().from, "AER");
//    ASSERT_EQUAL(tixs.back().from, "VKO");
//
//    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
//    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
//    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
//}

int main() {
    //TestRunner tr;
    //RUN_TEST(tr, TestSortBy);
}
