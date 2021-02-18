#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if(range_end-range_begin<3)
        return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto size = (range_end-range_begin)/3;
    //vector<typename RandomIt::value_type> part1(range_begin,  range_begin+size);
    //vector<typename RandomIt::value_type> part2(range_begin+size,  range_end);
    MergeSort(elements.begin(),elements.begin()+size);
    MergeSort(begin(elements)+size,begin(elements)+(size*2));
    MergeSort(begin(elements)+(size*2),end(elements));
    vector<typename RandomIt::value_type> back_inseter_;
    merge( begin(elements),begin(elements)+size,begin(elements)+size,begin(elements)+(2*size),back_inserter(back_inseter_));
    merge( begin(back_inseter_),end(back_inseter_),begin(elements)+(size*2),end(elements),range_begin);
}



int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

