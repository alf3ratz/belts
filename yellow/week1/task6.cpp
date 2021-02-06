#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Предварительное объявление шаблонных функций
template<typename T>
T Sqr(T t);

template<typename T>
vector<T> operator*(const vector<T>& left, const vector<T>& right);

template<typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value>& left,const map<Key, Value>& right);

template<typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& left,const pair<First, Second>& right);

template<typename T>
vector<T> operator*(const vector<T>& left,const vector<T>& right) {
    vector<T> newVect;
    newVect.reserve(left.size());
for (int i = 0; i < left.size(); ++i) {
        newVect.emplace_back(left.at(i)*right.at(i));
    }
    return newVect;
}

template<typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& left,const pair<First, Second>& right) {
    pair<First,Second> result = make_pair(left.first*right.first,left.second*right.second);
    return result;
}

template<typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value>& left,const  map<Key,Value>& right) {
    map<Key, Value> res;
    for (auto&[key, value]:left) {
        res[key] = left.at(key) * right.at(key);
    }
    return res;
}
template<typename T>
T Sqr(T t){
    return t*t;
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}
