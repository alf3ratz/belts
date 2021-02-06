#include <iostream>
#include <map>
using namespace std;
template <typename Key, typename  Value>
Value& GetRefStrict(map<Key,Value>& map, Key k);

template <typename Key, typename  Value>
Value& GetRefStrict(map<Key,Value>& map, Key k){
    auto res = map.count(k);
    if(res==0)
        throw runtime_error("");
    return map[k];
}


int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}
