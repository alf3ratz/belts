#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include "iomanip"

using namespace std;

struct Student {
    explicit Student(string name, string surname, int day, int month, int year) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->name = name;
        this->surname = surname;
    }

    string name;
    string surname;
    int day;
    int month;
    int year;
};


int main() {
    vector<Student> group;
    int num;
    int N, M, day, month, year;
    string name, surname, line;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> name >> surname>> day >> month >> year;
        group.emplace_back(Student(name, surname, day, month, year));
    }
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> line >> num;
        --num;
        if ((num) >= group.size() || (num) < 0) {
            cout << "bad request\n";
            continue;
        }
        if (line == "name") {
            cout << group[num].name << " " << group[num].surname << "\n";
        } else if (line == "date") {
            cout << group[num].day << "." << group[num].month << "." << group[num].year << "\n";
        } else
            cout << "bad request\n";
        
    }
    return 0;
}