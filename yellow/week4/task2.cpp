#include <algorithm>
#include <iostream>
#include <vector>
#include "set"

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
        vector<T> result;
        auto start = find_if(begin(elements),end(elements),[border](T i){return i > border;});
        for(auto i=start;i!=elements.end();i++)
            result.emplace_back(*i);
        return result;
}

int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
        cout << x << " ";
    }
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

