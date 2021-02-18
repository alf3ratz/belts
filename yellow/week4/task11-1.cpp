#include <iostream>
#include <deque>
#include <iterator>
#include "string"

using namespace std;



int main() {
    int n,N,num;
    cin>>n>>N;
    string operation;
    //string res = to_string(n);
    deque<string> res;
    res.push_back(to_string(n));
    for (int i = 0; i < N; ++i) {
        cin>>operation>>num;
        res.push_front("(");
        res.push_back(")");
        res.push_back(" "+operation);
        res.push_back(" "+to_string(num));
    }
    for(const auto& i: res)
        cout<<i;
    return 0;
}




