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

bool IsPalindrom(const string& str) {
    for (int i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
void TestPalindrom(){
    AssertEqual(IsPalindrom(""), true,"Zero symbols");
    AssertEqual(IsPalindrom("q"), true,"One symbol");
    AssertEqual(IsPalindrom(" q q "),true, "Empty letters");
    AssertEqual(IsPalindrom("rtr"), true,"First palindrom");
    AssertEqual(IsPalindrom("madam"),true, "Second palindrom");
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true,"Third palindrom");
    AssertEqual(IsPalindrom("k k"),true, "Fourth palindrom");
    AssertEqual(IsPalindrom("kk"),true, "Fifth palindrom");

}

void TestNotPalindrom(){
    AssertEqual(IsPalindrom("abc"), false,"Not a palindrom-1");
    AssertEqual(IsPalindrom("cabbad"), false,"Not a palindrom-2");
    AssertEqual(IsPalindrom("qwe rt ui  "), false,"Not a palindrom-3");
    AssertEqual(IsPalindrom("levEl"), false,"Not a palindrom-4");
    AssertEqual(IsPalindrom("qwe rt t r ewq"), false,"Not a palindrom-5");
    AssertEqual(IsPalindrom("awasitacaroracatisaw"), false,"Not a palindrom-6");
    AssertEqual(IsPalindrom("wasitaca oracatisaw"), false,"Not a palindrom-7");
    AssertEqual(IsPalindrom(" qwq  "),false, "Spaces-1");
    AssertEqual(IsPalindrom("q  w q"), false,"Spaces-2");
}

void TestAll(){
    TestRunner runner;
    runner.RunTest(TestPalindrom,"Is palindrom");
    runner.RunTest(TestNotPalindrom,"Isn't palindrom");
}

int main() {
    TestAll();
    // добавьте сюда свои тесты
    return 0;
}