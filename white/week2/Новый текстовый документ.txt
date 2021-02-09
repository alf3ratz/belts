#include <iostream>
#include <vector>

using namespace std;

vector<string> PalindromFilter(const vector<string> &words, int minLength) {
    vector<string> result;
    bool check = true;
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words[i].size() / 2; ++j) {
            if (words[i][j] != words[i][words[i].size() - j - 1])
                check = false;
        }
        if (check && words[i].size() >= minLength) {
            result.emplace_back(words[i]);
        }
        check=true;
    }
    return result;
}


int main() {

    //return 0;
}
