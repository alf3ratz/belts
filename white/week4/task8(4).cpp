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
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }
    cout << "OK" << endl;
    return 0;
}