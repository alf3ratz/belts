#include <iostream>
#include <deque>
#include <iterator>
#include "string"

using namespace std;

int main() {
    int n,N,num;
    cin>>n>>N;
    char operation,prev_operation;
    deque<string> res;
    res.push_back(to_string(n));
    for (int i = 0; i < N; ++i) {
        cin>>operation>>num;
        switch (operation) {
            case '+':
                res.push_back(" + ");
                res.push_back(to_string(num));
                prev_operation=operation;
                break;
            case '-':
                res.push_back(" - ");
                res.push_back(to_string(num));
                prev_operation=operation;
                break;
            case '*':
                if (prev_operation=='+' || prev_operation=='-') {
                    res.push_front("(");
                    res.push_back(")");
                }
                res.push_back(" * ");
                res.push_back(to_string(num));
                prev_operation=operation;
                break;
            case '/':
                if (prev_operation=='+' || prev_operation=='-') {
                    res.push_front("(");
                    res.push_back(")");
                }
                res.push_back(" / ");
                res.push_back(to_string(num));
                prev_operation=operation;
                break;
        }
    }
    for(const auto& i: res)
        cout<<i;
    return 0;
}




