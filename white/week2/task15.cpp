#include <iostream>
#include "set"
#include "map"

using namespace std;


int main() {
    map<string,set<string>> synonyms;
    int Q;
    cin>>Q;
    string task;
    for (int i = 0; i <Q ; ++i) {
        cin>>task;
        if(task=="ADD"){
            string word1,word2;
            cin>>word1>>word2;
            synonyms[word1].insert(word2);
            synonyms[word2].insert(word1);
        }else if(task=="CHECK"){
            string word1,word2;
            cin>>word1>>word2;
            if(synonyms[word1].count(word2)!=0||synonyms[word2].count(word1)!=0)
                cout<<"YES\n";
            else
                cout<<"NO\n";
        }else{
            string word;
            cin>>word;
            cout<<synonyms[word].size()<<"\n";
        }
    }
    return 0;
}