#include <algorithm>
#include <string>

using namespace std;

struct Specialization {
    string lenguage;
    explicit Specialization(string language_) {
        lenguage = language_;
    }
};

struct Course {
    string belt;

    explicit Course(string belt_) {
        belt = std::move(belt_);
    }
};

struct Week {
    string week;
    explicit Week(string week_) {
        week = week_;
    }

};
struct LectureTitle{
    string specialization;
    string course;
    string week;
    explicit LectureTitle(Specialization spec_,Course cs_,Week wk_){
        specialization=spec_.lenguage;
        course=cs_.belt;
        week=wk_.week;
    }
};



int main() {

}