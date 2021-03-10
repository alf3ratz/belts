#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <numeric>
#include <future>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other) {
        for (auto&[key, value]:other.word_frequences) {
            word_frequences[key] += other.word_frequences.at(key);
        }
    }
};

Stats ExploreLine(const set<string> &key_words, const string &s) {
//    Stats temp;
//    string_view str(s);
//    vector<string_view> line;
////    auto pos_view = str.find_first_not_of(" ");
////    str.remove_prefix(pos_view);
//    while (true) {
//        size_t space = str.find(' ');//=3
//        auto word = string(str.substr(0, space));
//        cout << word << " ";
//        if (key_words.count(word) > 0)
//            temp.word_frequences[move(word)]++;
//        if (space == str.npos) {
//            break;
//        } else {
//            str.remove_prefix(space + 1);//=элементы 45678
//        }
//    }
//    //if(!str.empty()){
//    if ((key_words.count(string(str)) > 0))
//        temp.word_frequences[move(string(str))]++;
//    //}
//    cout << endl;
//    return temp;
    string_view view = s;
    Stats result;
    size_t pos = view.find_first_not_of(' ');
    view.remove_prefix(pos);
    while (pos != string_view::npos) {
        pos = view.find_first_of(' ');

        auto key = std::string(view.substr(0, pos));

        if (key_words.count(key) > 0) {
            ++result.word_frequences[std::move(key)];
        }

        if (pos == string_view::npos)
            break;

        view.remove_prefix(pos);
        pos = view.find_first_not_of(' ');
        view.remove_prefix(pos);
    }

    return result;

}

Stats ExploreKeyWordsSingleThread(
        const set<string> &key_words, istream &input
) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    //Stats res_ = {map<string, int>{}};
    Stats res;
    vector<future<Stats>> arr;
    const auto threads_count = thread::hardware_concurrency();
    vector<stringstream> streams(threads_count);
    string line;
    size_t num_lines = 0;
    while (getline(input, line)) {
        streams[num_lines % threads_count] << line << '\n';
        ++num_lines;
    }
    arr.reserve(streams.size());
    for (auto &stream: streams) {
        arr.push_back(
                async(ExploreKeyWordsSingleThread, ref(key_words), ref(stream))
        );
    }
    for (auto &f: arr) {
        res += f.get();
    }


//    for (int i = 0; i < 4; ++i) {
//        res.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)).get());
//    }
    // Реализуйте эту функцию
    return res;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks",  2},
            {"sucks",  1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}