#include <iostream>
#include "algorithm"
#include "vector"
#include "string"

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> vect(N);
    for (auto &i:vect) {
        cin >> i;
    }

    sort(begin(vect), end(vect), [](string i, string j) {
        string tempI=i;
        string tempJ=j;
        for(auto& c: tempI){
            c=tolower(c);
        }
        for(auto& c: tempJ){
            c=tolower(c);
        }
        return tempI<tempJ;
    });
//    sort(begin(v), end(v),
//            // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
//         [](const string& l, const string& r) {
//             // сравниваем лексикографически...
//             return lexicographical_compare(
//                     // ... все символы строки l ...
//                     begin(l), end(l),
//                     // ... со всеми символами строки r ...
//                     begin(r), end(r),
//                     // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
//                     [](char cl, char cr) { return tolower(cl) < tolower(cr); }
//             );
//         }
//    );
    for (const auto &i:vect)
        cout << i << " ";
    return 0;
}