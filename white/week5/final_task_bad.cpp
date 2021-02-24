#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <set>
#include "iomanip"

using namespace std;

class Date {
public:
    Date() = default;

    explicit Date(int year, int month, int day) {
        this->year = year;
        if (month < 1 || month > 12) {
            string error = "Month value is invalid: " + to_string(month);
            throw invalid_argument(error);
        }
        this->month = month;
        if (day < 1 || day > 31) {
            string error = "Day value is invalid: " + to_string(day);
            throw invalid_argument(error);
        }
        this->day = day;
    }

    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }

    bool GetCheck() const { return check; }

    void SetCheck(bool ch) { check = ch; }

    string ToString() const {
        int year_count = (int) ceil(log10(abs(year) + 0.5));
        int month_count = (int) ceil(log10(abs(month) + 0.5));
        int day_count = (int) ceil(log10(abs(day) + 0.5));
        string str_year, str_month, str_day;
        for (int i = 0; i < 4 - year_count; ++i)
            str_year += "0";
        str_year += std::to_string(year);
        if (month_count == 1)
            str_month += "0";
        str_month += std::to_string(month);
        if (day_count == 1)
            str_day += "0";
        str_day += std::to_string(day);
        return str_year + "-" + str_month + "-" + str_day;
    }

private:
    int year{};
    int month{};
    int day{};
    bool check{};
};

bool operator<(const Date &lhs, const Date &rhs) {
    //if lhs!=rhs return lhs<rhs
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}


class Database {
public:

    void AddEvent(const Date &date, const string &event) {
        if (data.count(date) > 0) {
            data[date].insert(event);
        } else {
            set<string> events;
            events.insert(event);
            data[date] = events;
        }
    }

    bool DeleteEvent(const Date &date, const string &event) {
//        if (data.count(date) == 1) {
//            int num = 0;
//            bool check = false;
//            vector<string> events = data.at(date);
//            for (int i = 0; i < events.size(); ++i) {
//                if (data.at(date)[i] != event)
//                    num++;
//                else{
//                    data.at(date).erase(data.at(date).begin() + num);
//                    check=true;
//                    //i--;
//                }
//
//            }
//            if (!check) {
//                cout << "Event not found\n";
//                return false;
//            }
//            cout << "Deleted successfully\n";
//            return true;
//            //if(std::find(value.begin(), value.end(), event) != value.end())
//        }
//        cout << "Event not found\n";
//        return false;
        bool y;
        if (data[date].count(event) > 0) {
            data[date].erase(event);
        } else {
            return false;
        }
        return true;
    }

    int DeleteDate(const Date &date) {
        int N = data[date].size();
        data.erase(date);
        return N;
    }

    void Find(const Date &date) const {
        try{
            set<string> str = data.at(date);
            for (const auto &i : str) {
                cout << i << "\n";
            }
        } catch (exception& ex) {

        }


    }

    void Print() const {
        for (const auto&[key, value]:data) {
            for (const auto &i : value) {
                cout << key.ToString() << " " << i << "\n";
            }
        }
//        for (const auto &pair : data) {
//            for (const auto &event : pair.second) {
//                cout << setw(4) << setfill('0') << pair.first.GetYear() << '-';
//                cout << setw(2) << setfill('0') << pair.first.GetMonth() << '-';
//                cout << setw(2) << setfill('0') << pair.first.GetDay();
//                cout << " " << event << endl;
//            }
//        }
    }

private:
    map<Date, set<string>> data;
};

istream &operator>>(istream &str, Date &date) {
    string input;
    str >> input;
    stringstream stream(input);
    //stringstream ds(date);

    int year, month, day;

    if(!(stream >> year)){
        throw invalid_argument("Wrong date format: " + input);
    }
    if (stream.peek() != '-'){
        throw invalid_argument("Wrong date format: " + input);
    }
    stream.ignore(1);

    if(!(stream >> month)){
        throw invalid_argument("Wrong date format: " + input);
    }
    if (stream.peek() != '-'){
        throw invalid_argument("Wrong date format: " + input);
    }
    stream.ignore(1);

    if(!(stream >> day)){
        throw invalid_argument("Wrong date format: " +input);
    }
    if (!stream.eof()){
        throw invalid_argument("Wrong date format: " + input);
    }

    date =  Date(year, month, day);
    return str;
}

Date &operator-(const Date &lhs, const Date &rhs) {
    Date dt = Date(lhs.GetYear() - rhs.GetYear(), lhs.GetMonth() - rhs.GetMonth(), lhs.GetDay() - rhs.GetDay());
    return dt;

}

bool ParseDate(vector<string> date, Date &dt) {
    string res_ = "", res;
    try {
        for (int i = 0; i < date.size(); ++i) {
            res_ += date[i];
        }
        res = date[0] + date[1] + date[2];
        int year = stoi(date[0]);
        int month = stoi(date[1]);
        int day = stoi(date[2]);
        if (year < 0 || month <= 0 || day <= 0 || month > 12 || day > 31) {
            if (month > 12 || month <= 0) {
                cout << "Month value is invalid: " + to_string(month) + "\n";
                dt.SetCheck(false);
                return false;
            }
            if (day > 31 || day <= 0) {
                cout << "Day value is invalid: " + to_string(day) + "\n";
                dt.SetCheck(false);
                return false;
            }
            cout << "Wrong date format: " + res + "\n";
            dt.SetCheck(false);
            return false;
        }
        dt = Date(year, month, day);
        dt.SetCheck(true);
    } catch (exception &) {
        cout << "Wrong date format: " + res_ + "\n";
        return false;
    }
}

vector<string> Split(string str, string delimiter) {
    vector<string> data_in_line;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        data_in_line.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    data_in_line.push_back(str);
    return data_in_line;
}

int main() {

    Database db;
    vector<string> data_in_line;
    string data_line;
    while (getline(cin, data_line)) {
        try {
            stringstream stream(data_line);
            string command,str_date,event;
            Date date;
            stream >> command;
            if(command == "Print"){
                db.Print();
            }else if(command == ""){

            }else{
                try {
                    stream >> date;
                } catch (exception& ex) {
                    cout << ex.what() << endl;
                    break;
                }

                if (!stream.eof()) {
                    stream >> event;
                }
                if (command == "Add"&& !event.empty()) {
                   // stream.ignore(1);

//                    try {
//                        stream >> date;
//                    } catch (exception& ex) {
//                        cout << ex.what() << endl;
//                        break;
//                    }
//                    stream.ignore(1);
//                    string event;
//                    stream >> event;
                    db.AddEvent(date, event);
                } else if (command == "Del") {
                    //stream.ignore(1);
                    //Date date;
//                    try {
//                        stream >> date;
//                    } catch (exception& ex) {
//                        cout << ex.what() << endl;
//                        break;
//                    }
                    if (!event.empty()) {
//                        stream.ignore(1);
//                        string event;
//                        stream >> event;
                        if (db.DeleteEvent(date, event)) {
                            cout << "Deleted successfully" << endl;
                        } else {
                            cout << "Event not found" << endl;
                        }
                    } else {
                        int n = 0;
                        n = db.DeleteDate(date);
                        cout << "Deleted " << n << " events" << endl;
                    }

                } else if (command == "Find") {
//                    stream.ignore(1);
//                    //Date date;
//                    try {
//                        stream >> date;
//                    } catch (exception& ex) {
//                        cout << ex.what() << endl;
//                        break;
//                    }
                    db.Find(date);
                } else
                    throw runtime_error("Unknown command: " + command);
            }

        }
        catch (exception& ex) {
            cout << ex.what() << endl;
        }
    }
    return 0;
}



