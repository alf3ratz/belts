#include <algorithm>
#include <vector>
#include <iostream>

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


int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }
    cout << "OK" << endl;
    return 0;
}