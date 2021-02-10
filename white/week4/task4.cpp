#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    string str;
    while(getline(input, str)){
        cout << str << endl;
    }
    return 0;
}