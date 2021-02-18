#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "set"
#include "map"
#include "string"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix){
    auto l_bnd = lower_bound(range_begin, range_end,  prefix);
    auto u_bnd = upper_bound(range_begin, range_end,  prefix);

    while (u_bnd != range_end && string(begin(*u_bnd), begin((*u_bnd))+ prefix.size()) == prefix) {
        if (u_bnd == range_end)
            break;
        //if((*u_bnd)[0] == prefix)
        u_bnd++;
    }
    if (l_bnd == u_bnd) {
        if (l_bnd == range_begin)
            return make_pair(range_begin, range_begin);
        return make_pair(l_bnd, l_bnd);

    } else {
        return make_pair(l_bnd, u_bnd);
    }
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
         (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
         (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}




