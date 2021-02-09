#include <iostream>
#include "set"

using namespace std;


int main() {
    int N;
    cin>>N;
    string temp;
    set<string> unique_strings;
    for (int i = 0; i < N; ++i) {
        cin>>temp;
        unique_strings.insert(temp);
    }
    cout<<unique_strings.size()<<"\n";
    return 0;
}