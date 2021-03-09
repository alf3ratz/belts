#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    if (range_end - range_begin < 2)
        return;
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto size = (range_end - range_begin) / 3;
    MergeSort(elements.begin(), elements.begin() + size);
    MergeSort(begin(elements) + size, begin(elements) + (size * 2));
    MergeSort(begin(elements) + (size * 2), end(elements));
    vector<typename RandomIt::value_type> back_inseter_;
    merge(make_move_iterator(begin(elements)), make_move_iterator(begin(elements) + size),
          make_move_iterator(begin(elements) + size), make_move_iterator(begin(elements) + (2 * size)),
          move(back_inserter(back_inseter_)));
    merge(make_move_iterator(begin(back_inseter_)), make_move_iterator(end(back_inseter_)),
          make_move_iterator(begin(elements) + (size * 2)), make_move_iterator(end(elements)),
          range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}