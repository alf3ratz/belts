#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Human {
public:
    explicit Human(const string &name, const string &proffession) : name_(name), profession_(std::move(proffession)) {}

    string GetName() const {
        return name_;
    }

    string GetProfession() {
        return profession_;
    }

protected:
    virtual void Walk(const string &distantion) const = 0;

private:
    string name_, profession_;
};

class Student : public Human {
public:

    Student(const string &name, const string &favouriteSong) : Human(name, "Student"), favouriteSong_(favouriteSong) {}

    void Learn() {
        cout << "Student: " << GetName() << " learns" << endl;
    }

    void Walk(const string &destination) const override {
        cout << "Student: " << GetName() << " walks to: " << destination << endl;
        cout << "Student: " << GetName() << " sings a song: " << favouriteSong_ << endl;
    }

    void SingSong() {
        cout << "Student: " << GetName() << " sings a song: " << favouriteSong_ << endl;
    }

    string GetFavouriteSong() const {
        return favouriteSong_;
    }

private:
    string favouriteSong_;
};


class Teacher : public Human {
public:

    Teacher(const string &name, const string &subject) : Human(name, "Teacher"), subject_(subject) {}

    void Teach() {
        cout << "Teacher: " << GetName() << " teaches: " << subject_ << endl;
    }

    void Walk(const string &destination) const override {
        cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
    }

private:
    string subject_;
};


class Policeman : public Human {
public:
    Policeman(const string &name) : Human(name, "Policeman") {}

    void Check(Human &h) const {
        cout << "Policeman: " << h.GetName() << " checks " << h.GetProfession() << ". " << h.GetProfession()
             << "'s name is: " << h.GetName() << endl;
    }

    void Walk(const string &destination) const override {
        cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
    }

public:
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
