#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


int main() {
    int Q, count=0,num;
    cin >> Q;
    map<vector<string>, int> buses;
    for (int i = 0; i < Q; ++i) {
        cin>>num;
        vector<string> vec(num);
        for(auto& i: vec){
            cin >> i;
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