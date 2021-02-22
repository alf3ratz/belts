#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;

    virtual double Area() const = 0;

    virtual double Perimeter() const = 0;
};

class Circle : public Figure {
public:
    Circle(const double &r) {
        this->r = r;
    }

    virtual string Name() const override {
        return "CIRCLE";
    }

    virtual double Area() const override {
        return r * r * 3.14;
    }

    virtual double Perimeter() const override {
        return 2 * 3.14 * r;
    }

private:
    double r;
};

class Rect : public Figure {
public:
    Rect(const double &width, const double &height) {
        this->width = width;
        this->height = height;
    }

    string Name() const override {
        return "RECT";
    }

    virtual double Area() const override {
        return width * height;
    }

    virtual double Perimeter() const override {
        return 2 * (height + width);
    }

private:
    double width;
    double height;
};

class Triangle : public Figure {
public:
    Triangle(const double &a, const double &b, const double &c) : a(a), b(b), c(c) {
    }

    virtual string Name() const override {
        return "TRIANGLE";
    }

    virtual double Area() const override {
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    virtual double Perimeter() const override {
        return a + b + c;
    }

private:
    double a;
    double b;
    double c;
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
    string figure;
    is >> figure;

    if (figure == "RECT") {
        double w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    } else if (figure == "CIRCLE") {
        double r;
        is >> r;
        return make_shared<Circle>(r);
    } else {
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}