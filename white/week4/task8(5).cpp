#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

class Rational {
public:
    Rational() {
        numenator = 0;
        denumenator = 1;
    }

    Rational(int numerator, int denominator) {
        int denominator_ = denominator;
        int numenator_ = numerator;
        if (numerator < 0 && denominator < 0) {
            denominator_ *= (-1);
            numenator_ *= (-1);
        }
        if (denominator < 0 && numerator > 0) {
            denominator_ *= (-1);
        } else if (denominator > 0 && numerator < 0)
            numenator_ *= (-1);
        int a = numenator_;
        int b = denominator_;
        while (b > 0) {
            a %= b;
            swap(a, b);
        }
        this->numenator = numenator_ / a;
        this->denumenator = denominator_ / a;
        if (denominator < 0 && numerator > 0) {
            this->numenator *= (-1);
        } else if (denominator > 0 && numerator < 0)
            this->numenator *= (-1);
        if (numerator == 0) {
            this->numenator = 0;
            this->denumenator = 1;
        }
    }

    int Numerator() const {
        return numenator;
    }

    int Denominator() const {
        return denumenator;
    }


private:
    int numenator{};
    int denumenator;

};
bool operator<(const Rational& lhs, const Rational& rhs){
    double num1 = lhs.Numerator() * 1.0;
    double num2 = rhs.Numerator() * 1.0;
    return num1 / lhs.Denominator() < num2 / rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Denominator(),
            lhs.Denominator() * rhs.Numerator()
    };
}

ostream &operator<<(ostream &str, const Rational &rational) {
    str << rational.Numerator() << "/" << rational.Denominator();
    return str;
}

istream &operator>>(istream &str, Rational &rational) {
    int a, b;
    char symb;
    if (!(str >> a))
        return str;
    else{
        str>>symb;
        if(symb!='/')
            return str;
        if (!(str >> b))
            return str;
    }
    rational = Rational(a, b);
    return str;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }
    cout << "OK" << endl;
    return 0;
}