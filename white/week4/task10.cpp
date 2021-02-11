#include <algorithm>
#include <vector>
#include <iostream>
#include "exception"
#include "stdexcept"

using namespace std;

class Rational {
public:
    Rational() {
        numenator = 0;
        denumenator = 1;
    }

    Rational(const int& numerator, const int& denominator) {
        if (denominator == 0){
            throw invalid_argument("Invalid argument");
        }
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

bool operator<(const Rational &lhs, const Rational &rhs) {
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
    if (rhs.Numerator() == 0)
        throw domain_error("");
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
    else {
        str >> symb;
        if (symb != '/')
            return str;
        if (!(str >> b))
            return str;
    }
    rational = Rational(a, b);
    return str;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }
    cout<<"OK";
    return 0;
}