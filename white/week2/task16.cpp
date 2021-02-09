#include <iostream>
#include "set"
#include "map"
#include "vector"

using namespace std;


int main() {

    int Q, count=0,num;
    cin >> Q;
    map<set<string>, int> buses;
    for (int i = 0; i < Q; ++i) {
        cin>>num;
        set<string> vec;
        for (int j = 0; j < num; ++j) {
            string temp;
            cin>>temp;
            vec.insert(temp);
        }
        if (buses.count(vec) == 0){
            buses[vec] = ++count;
            cout << "New bus " << buses[vec] << "\n";
        } else{
            cout << "Already exists for " << buses[vec] << endl;
        }
    }
    return 0;
}