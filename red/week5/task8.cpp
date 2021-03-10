#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>

using namespace std;

template<typename Iterator>
struct IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : first(begin), last(end) {

    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

private:
    Iterator first;
    Iterator last;
};

template<typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        auto min_value = [&](Iterator itr) {
            return std::min<size_t>(std::distance(itr, end), page_size);
        };

        for (auto ptr = begin; ptr != end; ptr = std::next(ptr, min_value(ptr))) {
            pages.push_back(IteratorRange{ptr, std::next(ptr, min_value(ptr))});
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }

private:
    std::vector<IteratorRange<Iterator>> pages;
};

//-------------------------------------------------------------------------------------------------
template<typename C>
auto Paginate(C &c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

template <typename T>
int64_t SumRow(const T &rows) {
    int64_t res = 0;
    for (const auto &row: rows) {
        for (auto elem:row) {
            res += elem;
        }
    }
    return res;
}

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix) {
//    int64_t sum = 0;
//    vector<future<void>> temp;
//    for (auto &row:matrix) {
//        temp.push_back(
//                async([&sum, row] {
//                    SumRow(row, sum);
//                })
//        );
//    }
//    for (auto f: temp)
//        f.get();
    vector<future<int64_t>> res;
    int64_t sum=0;
    for (auto page:Paginate(matrix, 2000)) {
        res.push_back(
                async([=] {
                    return SumRow(page);
                })
        );
    }
    for(auto& f: res){
        sum+=f.get();
    }
    return sum;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}