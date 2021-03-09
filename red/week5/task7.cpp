#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class PriorityCollection {
public:
    using Id = size_t;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        sorted_ids.emplace(0, id);
        elements.emplace_back(std::move(object), 0);
        return Id(id++);
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        while (range_begin != range_end)
            *ids_begin++ = Add(std::move(*range_begin++));
        //elements.insert(range_begin, range_end, ids_begin);
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return elements[id].second >= 0;
//        for_each(sorted_objects.begin(), sorted_objects.end(), [id](pair<int, Id> a) {
//            if (a.second == id) {
//                return true;
//            }
//        });
//        return false;
    }

    // Получить объект по идентификатору
    const T &Get(Id id) const {
        return elements[id].first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        //auto new_priority = elements[id].second++;
        //auto old_priority = new_priority++;
        sorted_ids.erase({elements[id].second, id});
        elements[id].second++;
        sorted_ids.insert({elements[id].second, id});
//        auto it = find(sorted_objects.begin(),sorted_objects.end(),[id](pair<int, Id> a) {
//            if (a.second == id) {
//                a.first++;
//                return;
//            }
//        });
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const {
        return elements[prev(sorted_ids.end())->second];
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {

        auto id = prev(end(sorted_ids))->second;
       // sorted_objects.erase(prev(sorted_objects.end()));
        auto pair_with_elem = move(elements[id]);
        sorted_ids.erase({pair_with_elem.second, id});
        elements[id] = {T(), -1};
        ///elements.erase({pair_with_elem.first,id});
        //elements.erase(elements.begin() + id);
        return pair_with_elem;

    }

private:
    int id = 0;
    std::set<std::pair<int, Id>> sorted_ids;
    std::vector<std::pair<T, int>> elements;

};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;

    StringNonCopyable(StringNonCopyable &&) = default;

    StringNonCopyable &operator=(const StringNonCopyable &) = delete;

    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}