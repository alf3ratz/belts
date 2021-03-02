#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;


template <class T>
class ObjectPool {
public:
    ObjectPool():ejected_count(0),allocated_count(0){};
    T* Allocate(){
        if(ejected.size()>0){
            auto temp = ejected.front();
            allocated.insert(temp);
            ejected_count--;
            ejected.pop_front();
            return temp;
        }else{
            T* free = new T;
            allocated.insert(free);
            return free;
        }
    }
    T* TryAllocate(){
        if(ejected.size()<=0)
            return nullptr;
        return Allocate();
    }

    void Deallocate(T* object){
        auto iter = allocated.find(object);
        if(iter!=allocated.end()){
            ejected.push_back(*iter);
            allocated.erase(object);
            return;
        }
        throw invalid_argument("There is no such element!");
    }

    template<typename U>
    void Del(U collection){
        for(auto& item:collection)
            delete item;
    }
    ~ObjectPool(){
        Del(allocated);
        Del(ejected);
    }

private:
    int64_t ejected_count;
    int64_t allocated_count;
    set<T*> allocated;
    deque<T*> ejected;
    // Добавьте сюда поля

};

template<class T>


void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    //TestRunner tr;
    //tr.RunTest(TestObjectPool, "TestObjectPool");

    //RUN_TEST(tr, TestObjectPool);
    return 0;
}