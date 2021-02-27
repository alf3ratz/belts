
#include <iostream>
#include <string>
#include <sstream>
#include "vector"
#include "set"

using namespace std;


class Learner {
private:
    vector<string> dict;
    set<string> dictionary;

public:
    int Learn(const vector<string> &words) {
        int newWords = 0;
        for (const auto &word:words) {
            if (dictionary.count(word) != 1) {
                ++newWords;
                dictionary.insert(word);
            }

        }
        return newWords;
    }

    vector<string> KnownWords() {
        vector<string> res;
        res.insert(res.end(), dictionary.begin(), dictionary.end());
        return res;
    }
};


int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}