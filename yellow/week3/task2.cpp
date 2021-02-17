#include <iostream>
#include "phone_number.h"
#include <algorithm>
#include <vector>

PhoneNumber::PhoneNumber(const string &international_number) {
    vector<string> data_in_line;
    string delimiter = "-", str = international_number;
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        data_in_line.push_back(token);
        str.erase(0, pos + delimiter.length());
        count++;
        if (count == 2)
            break;
    }
    data_in_line.push_back(str);
    if (data_in_line.size() != 3 || data_in_line[0][0] != '+' || data_in_line[0].empty() || data_in_line[1].empty() ||
        data_in_line[2].empty())
        throw invalid_argument("wrong phone format!");
    data_in_line[0] = data_in_line[0].substr(1, data_in_line[0].size() - 1);
    this->country_code_ = data_in_line[0];
    this->city_code_ = data_in_line[1];
    this->local_number_ = data_in_line[2];
}

string PhoneNumber::GetCountryCode() const {
    return this->country_code_;
}

string PhoneNumber::GetCityCode() const {
    return this->city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return this->local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}
