#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector() : size_(0),capacity_(0) {
        data= nullptr;
        end_= nullptr;
    }

    explicit SimpleVector(size_t size) : size_(size), capacity_(size) {
        data = new T[size];
        end_ = data + size;
    }

    ~SimpleVector() {
        delete[] data;
        //delete end_;
    }

    T &operator[](size_t index) {
        return data[index];
    }

    T *begin() {
        return data;
    }

    T *end() {
        return end_;
    }

    const T *begin() const { return data; }

    const T *end() const { return end_; }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T &value) {
        if (data == nullptr) {
            data = new T[1];
            capacity_ = 1;
        } else if(capacity_==size_){
            T* temp_vect = new T[capacity_*2];
            for (int i = 0; i < capacity_; ++i) {
                temp_vect[i]=data[i];
            }
            delete[] data;
            data = temp_vect;
            capacity_*=2;
        }
        *(data + size_) = value;
        size_++;
        end_ = data + size_;
    }

private:
    T *data;
    T *end_;
    size_t size_;
    size_t capacity_;
};
