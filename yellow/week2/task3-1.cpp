#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};
//
//class Person {
//public:
//    // Вы можете вставлять сюда различные реализации класса,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//    void ChangeFirstName(int year, const string& first_name) {
//    }
//    void ChangeLastName(int year, const string& last_name) {
//    }
//    string GetFullName(int year) {
//    }
//};

void TestChangeFirstName(){
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1968),"Polina Sergeeva","TestFirstNameChange-1");
    person.ChangeFirstName(1969, "Maria");
    AssertEqual(person.GetFullName(1970),"Maria Sergeeva","TestFirstNameChange-2");
}
void TestIncognito(){
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1964),"Incognito","TestIncognito-1");

}
void TestFirstNameWithoutLast(){
    Person person;
    person.ChangeFirstName(1965, "Polina");
    AssertEqual(person.GetFullName(1966),"Polina with unknown last name","TestWithoutLastname-1");
}
void TestLastNameWithoutFirst(){
    Person person;
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1967),"Sergeeva with unknown first name","TestWithoutFirstname-1");
}
void TestFullName(){

}

void TestAll(){
    TestRunner runner;
    runner.RunTest(TestChangeFirstName,"Change first name test");
    runner.RunTest(TestFirstNameWithoutLast,"Change first name only");
    runner.RunTest(TestLastNameWithoutFirst,"Change last name only");
    runner.RunTest(TestIncognito,"Check empty name");
    runner.RunTest(TestFullName,"Test full person name");
}

int main() {
    TestAll();
    // добавьте сюда свои тесты
    return 0;
}