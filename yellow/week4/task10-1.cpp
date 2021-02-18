#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "set"
#include "map"
#include "string"

using namespace std;


template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix) {
    auto l_bnd = lower_bound(range_begin, range_end, string(1, prefix));
    auto u_bnd = upper_bound(range_begin, range_end, string(1, prefix));

    while (u_bnd != range_end && (*u_bnd)[0] == prefix) {
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
    //return make_pair(range_begin, range_end);

}


int main() {
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
         (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
         (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}




