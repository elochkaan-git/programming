#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


template<typename T>
class Box
{
private:
    std::unique_ptr<T[]> data_begin_;
    size_t size_;
    size_t capacity_;

public:
    Box();
    Box(size_t n);
    Box(size_t n, T value);
    Box(Box& copy);
    Box(Box&& moved);
    ~Box() = default;

    T& operator [](size_t pos);
    Box& operator =(Box& other);
    Box& operator =(Box&& other);

    T& at(size_t n);
    void open() const;
    void push_back(T value);
    void insert(T value, size_t pos);
    void erase(size_t pos);
    size_t size() const;

    class Iterator
    {
    private:
        Box* box_ptr_;
        size_t current_index_;
    
    public:
        Iterator(Box* box, size_t index);

        T& operator *();
        bool operator !=(Box<T>::Iterator& other);
        bool operator ==(Box<T>::Iterator& other);
        void operator ++();
    };

    Iterator begin();
    Iterator end();
};

template<typename T>
Box<T>::Box()
    : data_begin_(nullptr)
    , size_(0)
    , capacity_(0)
{
}

template<typename T>
Box<T>::Box(size_t n)
    : data_begin_(std::make_unique<T[]>(n))
    , size_(0)
    , capacity_(n)
{
}

template<typename T>
Box<T>::Box(size_t n, T value)
    : data_begin_(std::make_unique<T[]>(n))
    , size_(n)
    , capacity_(n)
{
    for(size_t i = 0; i < n; ++i) data_begin_[i] = value;
}

template<typename T>
Box<T>::Box(Box& copy)
    : data_begin_(std::make_unique<T[]>(copy.capacity_))
    , size_(copy.size_)
    , capacity_(copy.capacity_)
{
    for(size_t i = 0; i < copy.size_; ++i) data_begin_[i] = copy.data_begin_[i];
}

template<typename T>
Box<T>::Box(Box&& moved)
    : data_begin_(std::move(moved.data_begin_))
    , size_(std::move(moved.size_))
    , capacity_(std::move(moved.capacity_))
{
}

template<typename T>
T& Box<T>::operator[](size_t pos)
{
    return data_begin_[pos];
}

template<typename T>
Box<T>& Box<T>::operator =(Box& other)
{
    data_begin_ = std::make_unique<T[]>(other.capacity_);
    for(size_t i = 0; i < other.size_; ++i) data_begin_[i] = other[i];
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

template<typename T>
Box<T>& Box<T>::operator =(Box&& other)
{
    data_begin_ = std::move(other.data_begin_);
    size_ = std::move(other.size_);
    capacity_ = std::move(other.capacity_);

    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

template<typename T>
T& Box<T>::at(size_t n)
{
    if(n >= size_) throw std::out_of_range("You're out of the Box! n must be less than " + std::to_string(size_));
    return data_begin_[n];
}

template<typename T>
void Box<T>::push_back(T value) {
    if(size_ < capacity_) {
        data_begin_[size_] = value;
        ++size_;
    }
    else {
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
        for(size_t i = 0; i < size_; ++i) new_data[i] = data_begin_[i];
        new_data[size_] = value;
        data_begin_ = std::move(new_data);
        ++size_;
    }
}

template<typename T>
void Box<T>::insert(T value, size_t pos)
{
    if(pos >= size_) throw std::out_of_range("You're out of the Box! n must be less than " + std::to_string(size_));
    if(size_ == capacity_) capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
    ++size_;
    
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
    for(size_t i = 0, j = 0; i < size_; ++i)
        if(i == pos) new_data[i] = value;
        else new_data[i] = data_begin_[j++];
    data_begin_ = std::move(new_data);
}

template<typename T>
void Box<T>::erase(size_t pos)
{
    if(pos >= size_) throw std::out_of_range("You're out of the Box! n must be less than " + std::to_string(size_));
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
    for(size_t i = 0, j = 0; i < size_; ++i)
        if(i != pos) new_data[j++] = data_begin_[i];
    data_begin_ = std::move(new_data);
    --size_;
}

template<typename T>
size_t Box<T>::size() const
{
    return size_;
}

template<typename T>
void Box<T>::open() const
{
    for(size_t i = 0; i < size_; ++i) std::cout << *(data_begin_.get() + i) << ' ';
}


template<typename T>
typename Box<T>::Iterator Box<T>::begin()
{
    return {this, 0};
}

template<typename T>
typename Box<T>::Iterator Box<T>::end()
{
    return {this, size_};
}


template<typename T>
Box<T>::Iterator::Iterator(Box<T>* box, size_t index)
    : box_ptr_(box)
    , current_index_(index)
{
}

template<typename T>
T& Box<T>::Iterator::operator*()
{
    return box_ptr_->data_begin_[current_index_];
}

template<typename T>
bool Box<T>::Iterator::operator !=(Box<T>::Iterator& other)
{
    return current_index_ != other.current_index_;
}

template<typename T>
bool Box<T>::Iterator::operator ==(Box<T>::Iterator& other)
{
    return current_index_ == other.current_index_;
}

template<typename T>
void Box<T>::Iterator::operator ++()
{
   ++current_index_;
}