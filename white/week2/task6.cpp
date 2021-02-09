#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v){
    vector<int> result;
    for (int i = v.size()-1; i >=0 ; --i) {
        result.emplace_back(v[i]);
    }
    return result;
}

int main() {

    //return 0;
}
