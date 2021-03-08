#pragma once

#include <cstdlib>
#include <algorithm>
#ifndef UNTITLED9_SIMPLE_VECTOR_H
#define UNTITLED9_SIMPLE_VECTOR_H


// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector() : size_(0), capacity_(0) {
        data = nullptr;
        end_ = nullptr;
    }
    SimpleVector(const SimpleVector& sv);

    explicit SimpleVector(size_t size) : size_(size), capacity_(size) {
        data = new T[size];
        end_ = data + size;
    }

    SimpleVector &operator=(const SimpleVector &other);

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
        } else if (capacity_ == size_) {
            T *temp_vect = new T[capacity_ * 2];
            for (int i = 0; i < capacity_; ++i) {
                temp_vect[i] = data[i];
            }
            delete[] data;
            data = temp_vect;
            capacity_ *= 2;
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
template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& sv) : size_(sv.size_), capacity_(sv.capacity_), data(new T[sv.capacity_]),end_(data+sv.size_)
{
    std::copy(sv.begin(), sv.end(), begin());
}
template<typename T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector<T> &rhs) {
//    if (&other == this) return *this;
//    if (capacity_ < other.size_) {
////        SimpleVector<T> simp = SimpleVector<T>(other.size_);
////        simp.data = other.data;
////        simp.capacity_ = other.capacity_;
////        std::swap(simp.data, data);
////        std::swap(simp.size_, size_);
////        std::swap(simp.capacity_, capacity_);
//    } else {
//        std::copy(other.begin(), other.end(), begin());
//        size_ = other.size_;
//    }
//    return *this;
    //if (this == &rhs) return *this;

    if (rhs.size_ <= capacity_)
    {
        std::copy(rhs.begin(), rhs.end(), begin());
        size_ = rhs.size_;
    }
    else
    {
        SimpleVector<T> tmp(rhs);
        std::swap(tmp.data, data);
        std::swap(tmp.size_, size_);
        std::swap(tmp.capacity_, capacity_);
        std::swap(tmp.end_,end_);
    }
    return *this;
    //copy(other.begin(),other.end(),data);
}

#endif //UNTITLED9_SIMPLE_VECTOR_H
