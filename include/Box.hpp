#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>


template<typename T>
class Box
{
private:
    T* data_begin_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    std::allocator<T> alloc_;

public:
    Box();
    Box(size_t n);
    Box(size_t n, T value);
    Box(Box& copy);
    Box(Box&& moved);
    ~Box();

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
        Box* box_ptr_ = nullptr;
        size_t current_index_ = 0;
    
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
Box<T>::Box() {
    data_begin_ = alloc_.allocate(0);
    capacity_ = 0;
    size_ = 0;
}

template<typename T>
Box<T>::Box(size_t n) {
    data_begin_ = alloc_.allocate(n);
    capacity_ = n;
    size_ = 0;
}

template<typename T>
Box<T>::Box(size_t n, T value) {
    data_begin_ = alloc_.allocate(n);
    for(size_t i = 0; i < n; ++i) {
        alloc_.construct(data_begin_ + i, value);
    }
    capacity_ = n;
    size_ = n;
}

template<typename T>
Box<T>::Box(Box& copy) {
    T* new_data = alloc_.allocate(copy.capacity_);
    for(size_t i = 0; i < copy.size_; ++i) alloc_.construct(new_data + i, *(copy.data_begin_ + i));
    data_begin_ = new_data;
    size_ = copy.size_;
    capacity_ = copy.capacity_;
}

template<typename T>
Box<T>::Box(Box&& moved) {
    data_begin_ = moved.data_begin_;
    size_ = moved.size_;
    capacity_ = moved.capacity_;
    moved.data_begin_ = nullptr;
}

template<typename T>
Box<T>::~Box() {
    alloc_.deallocate(data_begin_, capacity_);
}

template<typename T>
T& Box<T>::operator[](size_t pos) {
    return *(data_begin_ + pos);
}

template<typename T>
Box<T>& Box<T>::operator =(Box& other) {
    data_begin_ = alloc_.allocate(other.capacity_);
    for(size_t i = 0; i < other.size_; ++i) alloc_.construct(data_begin_ + i, *(other.data_begin_ + i));
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

template<typename T>
Box<T>& Box<T>::operator =(Box&& other) {
    data_begin_ = other.data_begin_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_begin_ = nullptr;
    return *this;
}

template<typename T>
T& Box<T>::at(size_t n)
{
    if(data_begin_ + n >= data_begin_ + size_) throw std::out_of_range("You're out of the Box");
    return *(data_begin_ + n);
}

template<typename T>
void Box<T>::push_back(T value) {
    if(size_ < capacity_) {
        *(data_begin_ + size_) = value;
        ++size_;
    }
    else {
        capacity_ += 2;
        T* new_data = alloc_.allocate(capacity_);
        for(size_t i = 0; i < size_; ++i) alloc_.construct(new_data + i, *(data_begin_ + i));
        *(new_data + size_) = value;
        alloc_.deallocate(data_begin_, capacity_);
        data_begin_ = new_data;
        ++size_;
    }
}

template<typename T>
void Box<T>::insert(T value, size_t pos) {
    if(data_begin_ + pos >= data_begin_ + size_) throw std::out_of_range("You're out of the Box");
    if(size_ == capacity_) ++capacity_;

    T* new_data = alloc_.allocate(capacity_);
    for(size_t i = 0; i < size_; ++i)
        if(i == pos) alloc_.construct(new_data + i, value);
        else if(i < pos) alloc_.construct(new_data + i, *(data_begin_ + i));
        else alloc_.construct(new_data + i, *(data_begin_ + i - 1));
    alloc_.deallocate(data_begin_, capacity_);
    data_begin_ = new_data;
    ++size_;    
}

template<typename T>
void Box<T>::erase(size_t pos) {
    if(data_begin_ + pos >= data_begin_ + size_) throw std::out_of_range("You're out of the Box");
    T* new_data = alloc_.allocate(capacity_);
    for(size_t i = 0; i < size_; ++i)
        if(i < pos) alloc_.construct(new_data + i, *(data_begin_ + i));
        else if(i > pos) alloc_.construct(new_data + i - 1, *(data_begin_ + i));
    alloc_.deallocate(data_begin_, capacity_);
    data_begin_ = new_data;
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
    for(size_t i = 0; i < size_; ++i) std::cout << *(data_begin_ + i) << ' ';
}


template<typename T>
typename Box<T>::Iterator Box<T>::begin() {
    return {this, 0};
}

template<typename T>
typename Box<T>::Iterator Box<T>::end() {
    return {this, size_};
}


template<typename T>
Box<T>::Iterator::Iterator(Box<T>* box, size_t index) {
    box_ptr_ = box;
    current_index_ = index;
}

template<typename T>
T& Box<T>::Iterator::operator*() {
    return *(box_ptr_->data_begin_ + current_index_);
}

template<typename T>
bool Box<T>::Iterator::operator !=(Box<T>::Iterator& other) {
    return current_index_ != other.current_index_;
}

template<typename T>
bool Box<T>::Iterator::operator ==(Box<T>::Iterator& other) {
    return current_index_ == other.current_index_;
}

template<typename T>
void Box<T>::Iterator::operator ++() {
   ++current_index_;
}