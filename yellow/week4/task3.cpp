#include <algorithm>
#include <iostream>
#include <vector>
#include "set"

using namespace std;

vector<string> SplitIntoWords(const string &s) {
    vector<string> result;
    auto start = s.begin();
    while (start != s.end()) {
        auto temp = find(start, end(s), ' ');
        result.emplace_back(string(start, temp));
        if (temp != s.end())
            temp++;
        start = temp;

        //string s2(std::begin(s), std::find(std::begin(s), std::end(s), ' '));
        //auto temp = find(begin(s), end(s), ' ');
        //result.push_back(s2);
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}

