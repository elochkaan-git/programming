#pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>


template<typename T>
struct NodeDL {
    T value_;
    std::unique_ptr<NodeDL<T>> next_;
    NodeDL<T>* prev_;

    NodeDL(T value) 
        : value_(value)
        , next_(nullptr)
        , prev_(nullptr)
    {
    }
};


template<typename T>
class DoubleList
{
private:
    std::unique_ptr<NodeDL<T>> root_;
    NodeDL<T>* tail_;
    size_t size_;

public:
    DoubleList();
    DoubleList(size_t n, T value);
    DoubleList(DoubleList& copy);
    DoubleList(DoubleList&& moved);

    T& operator [](size_t pos);
    DoubleList& operator =(DoubleList& other);
    DoubleList& operator =(DoubleList&& other);

    void open() const;
    void push_back(T value);
    void insert(T value, size_t pos);
    void erase(size_t pos);
    void clear();
    size_t size() const;

    class Iterator
    {
    private:
        DoubleList* list_ptr_ = nullptr;
        NodeDL<T>* current_node_ = nullptr;
    
    public:
        Iterator(DoubleList* list, NodeDL<T>* index);

        T& operator *();
        bool operator !=(const DoubleList<T>::Iterator& other) const;
        bool operator ==(const DoubleList<T>::Iterator& other) const;
        void operator ++();
    };

    class ReverseIterator
    {
    private:
        DoubleList* list_ptr_ = nullptr;
        NodeDL<T>* current_node_ = nullptr;
    
    public:
        ReverseIterator(DoubleList* list, NodeDL<T>* index);

        T& operator *();
        bool operator !=(const DoubleList<T>::ReverseIterator& other) const;
        bool operator ==(const DoubleList<T>::ReverseIterator& other) const;
        void operator ++();
    };

    Iterator begin();
    ReverseIterator rbegin();
    Iterator end();
    ReverseIterator rend();
};

template<typename T>
DoubleList<T>::DoubleList()
    : root_(nullptr)
    , tail_(nullptr)
    , size_(0)
{
}

template<typename T>
DoubleList<T>::DoubleList(size_t n, T value)
    : root_(std::make_unique<NodeDL<T>>(value))
    , tail_(nullptr)
    , size_(n)
{
    NodeDL<T>* current = root_.get();

    for(size_t i = 1; i < n; ++i) {
        current->next_ = std::make_unique<NodeDL<T>>(value);
        current->next_->prev_ = current;
        current = current->next_.get();
    }
    tail_ = current;
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList& copy)
    : root_(nullptr)
    , tail_(nullptr)
    , size_(copy.size_)
{
    if(copy.root_) {
        root_ = std::make_unique<NodeDL<T>>(copy.root_->value_);
        NodeDL<T>* _this = root_.get();
        NodeDL<T>* _copy = copy.root_.get();

        while(_copy->next_) {
            _this->next_ = std::make_unique<NodeDL<T>>(_copy->next_->value_);
            _this = _this->next_.get();
            _copy = _copy->next_.get();
        }

        tail_ = _this;
    }
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList&& moved)
{
    root_ = std::move(moved.root_);
    tail_ = moved.tail_;
    size_ = moved.size_;

    moved.tail_ = nullptr;
    moved.size_ = 0;
}

template<typename T>
T& DoubleList<T>::operator[](size_t pos)
{
    NodeDL<T>* current = root_.get();
    for(size_t i = 0; i < size_; ++i) {
        if(i == pos) return current->value_;
        else current = current->next_.get();
    }
    throw std::out_of_range("You are out of list");
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator =(DoubleList& other)
{
    clear();
    if(!other.root_) {
        root_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }
    else {
        root_ = std::make_unique<NodeDL<T>>(other.root_->value_);
        NodeDL<T>* _this = root_.get();
        NodeDL<T>* _copy = other.root_.get();

        while(_copy->next_) {
            _this->next_ = std::make_unique<NodeDL<T>>(_copy->next_->value_);
            _this = _this->next_.get();
            _copy = _copy->next_.get();
        }

        tail_ = _this;
        size_ = other.size_;
    }

    return  *this;
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator =(DoubleList&& other)
{
    root_ = std::move(other.root_);
    tail_ = other.tail_;
    size_ = other.size_;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
}

template<typename T>
void DoubleList<T>::push_back(T value)
{
    if(!root_) {
        root_ = std::make_unique<NodeDL<T>>(value);
        tail_ = root_.get();
    }
    else {
        tail_->next_ = std::make_unique<NodeDL<T>>(value);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_.get();
    }
    ++size_;
}

template<typename T>
void DoubleList<T>::insert(T value, size_t pos)
{
    if(pos > size_) throw std::out_of_range("You're out of the DoubleList");
    else if(pos == size_) push_back(value);
    else if(pos == 0) {
        std::unique_ptr<NodeDL<T>> new_node = std::make_unique<NodeDL<T>>(value);
        new_node->next_ = std::move(root_);
        root_ = std::move(new_node);
        root_->next_->prev_ = root_.get();
        ++size_;
    }
    else {
        size_t i = 0;
        NodeDL<T>* current = root_.get();
        while(i != pos) {
            current = current->next_.get();
            ++i;
        }
        std::unique_ptr<NodeDL<T>> new_node = std::make_unique<NodeDL<T>>(value);
        new_node->prev_ = current->prev_;
        new_node->next_ = std::move(current->prev_->next_);
        new_node->prev_->next_ = std::move(new_node);
        current->prev_ = current->prev_->next_.get();
        ++size_;
    }
}

template<typename T>
void DoubleList<T>::erase(size_t pos)
{
    if(pos >= size_) throw std::out_of_range("You're out of the DoubleList");
    else if(size_ == 1) {
        clear();
    }
    else if(pos == size_ - 1) {
        tail_ = tail_->prev_;
        tail_->next_.reset();
    }
    else if(pos == 0) {
        root_ = std::move(root_->next_);
        root_->prev_ = nullptr;
    }
    else {
        size_t i = 0;
        NodeDL<T>* current = root_.get();
        while(i != pos) {
            current = current->next_.get();
            ++i;
        }
        current->next_->prev_ = current->prev_;
        current->prev_->next_ = std::move(current->next_);
    }
    --size_;
}

template<typename T>
void DoubleList<T>::clear()
{
    root_.reset();
    tail_ = nullptr;
    size_ = 0;
}

template<typename T>
size_t DoubleList<T>::size() const
{
    return size_;
}

template<typename T>
void DoubleList<T>::open() const
{      
    NodeDL<T>* current = root_.get();
    while(current) {
        std::cout << current->value_ << ' ';
        current = current->next_.get();
    }
}


template<typename T>
typename DoubleList<T>::Iterator DoubleList<T>::begin() {
    return {this, root_.get()};
}

template<typename T>
typename DoubleList<T>::ReverseIterator DoubleList<T>::rbegin() {
    return {this, tail_};
}

template<typename T>
typename DoubleList<T>::Iterator DoubleList<T>::end() {
    return {this, nullptr};
}

template<typename T>
typename DoubleList<T>::ReverseIterator DoubleList<T>::rend() {
    return {this, nullptr};
}


template<typename T>
DoubleList<T>::Iterator::Iterator(DoubleList<T>* list, NodeDL<T>* node) {
    list_ptr_ = list;
    current_node_ = node;
}

template<typename T>
T& DoubleList<T>::Iterator::operator*() {
    return current_node_->value_;
}

template<typename T>
bool DoubleList<T>::Iterator::operator !=(const DoubleList<T>::Iterator& other) const {
    return current_node_ != other.current_node_;
}

template<typename T>
bool DoubleList<T>::Iterator::operator ==(const DoubleList<T>::Iterator& other) const {
    return current_node_ == other.current_node_;
}

template<typename T>
void DoubleList<T>::Iterator::operator ++() {
   current_node_ = current_node_->next_.get();
}


template<typename T>
DoubleList<T>::ReverseIterator::ReverseIterator(DoubleList<T>* list, NodeDL<T>* node) {
    list_ptr_ = list;
    current_node_ = node;
}

template<typename T>
T& DoubleList<T>::ReverseIterator::operator*() {
    return current_node_->value_;
}

template<typename T>
bool DoubleList<T>::ReverseIterator::operator !=(const DoubleList<T>::ReverseIterator& other) const {
    return current_node_ != other.current_node_;
}

template<typename T>
bool DoubleList<T>::ReverseIterator::operator ==(const DoubleList<T>::ReverseIterator& other) const {
    return current_node_ == other.current_node_;
}

template<typename T>
void DoubleList<T>::ReverseIterator::operator ++() {
   current_node_ = current_node_->prev_;
}