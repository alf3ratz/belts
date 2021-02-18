#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> vec;
    vector<string> res;
    for (int i = 0; i < n; ++i)
        vec.push_back(i + 1);
    sort(vec.rbegin(),vec.rend());
    do
    {
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout<<'\n';
    }while(std::prev_permutation(vec.begin(), vec.end()));
    return 0;
}

