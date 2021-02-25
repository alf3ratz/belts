#include <iostream>
#include <sstream>

#pragma once

using namespace std;

class Date {
public:
    Date();
    Date(int year, int month, int day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

ostream &operator<<(ostream& os, const Date& date);

Date ParseDate(istream& is);
