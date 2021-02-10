#include <iostream>
#include "algorithm"
#include "vector"

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> vect(N);
    for (auto &i:vect) {
        cin >> i;
    }
    sort(begin(vect),end(vect),[](int i,int j){return abs(i)<abs(j);});
    for(const auto& i:vect)
        cout<<i<<" ";
    return 0;
}