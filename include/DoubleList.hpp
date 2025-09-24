#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>


template<typename T>
struct NodeDL {
    T value_;
    NodeDL* next_;
    NodeDL* prev_;

    NodeDL(T value, NodeDL* next, NodeDL* prev) {
        value_ = value;
        next_ = next;
        prev_ = prev;
    }
};


template<typename T>
class DoubleList
{
private:
    NodeDL<T>* root_ = nullptr;
    NodeDL<T>* tail_ = nullptr;
    size_t size_ = 0;

public:
    DoubleList();
    DoubleList(size_t n, T value);
    DoubleList(DoubleList& copy);
    DoubleList(DoubleList&& moved);
    ~DoubleList();

    T& operator [](size_t pos);
    DoubleList& operator =(DoubleList& other);
    DoubleList& operator =(DoubleList&& other);

    // T& at(size_t n);
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
DoubleList<T>::DoubleList() {
    root_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

template<typename T>
DoubleList<T>::DoubleList(size_t n, T value) {
    root_ = new NodeDL<T>(value, nullptr, nullptr);
    NodeDL<T>* current = root_;

    for(size_t i = 1; i < n; ++i) {
        NodeDL<T>* leaf = new NodeDL<T>(value, nullptr, current);
        current->next_ = leaf;
        current = leaf;
    }
    size_ = n;
    tail_ = current;
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList& copy) {
    if(!copy.root_) {
        root_ = NULL;
        tail_ = NULL;
        size_ = 0;
    }
    else {
        root_ = new NodeDL<T>(copy.root_->value_, copy.root_->next_, nullptr);
        NodeDL<T>* current = root_;

        while(current->next_ != nullptr) {
            NodeDL<T>* new_node = new NodeDL<T>(current->next_->value_, current->next_->next_, current);
            current->next_ = new_node;
            current = new_node;
        }

        tail_ = current;
        size_ = copy.size_;
    }
}

template<typename T>
DoubleList<T>::DoubleList(DoubleList&& moved) {
    root_ = moved.root_;
    tail_ = moved.tail_;
    size_ = moved.size_;
    moved.root_ = nullptr;
    moved.tail_ = nullptr;
}

template<typename T>
DoubleList<T>::~DoubleList() {
    if(!root_) return;

    NodeDL<T>* begin = root_;
    NodeDL<T>* next = nullptr;
    while(begin != tail_) {
        next = begin->next_;
        delete begin;
        begin = next;
    }
    delete tail_;
}

template<typename T>
T& DoubleList<T>::operator[](size_t pos) {
    NodeDL<T>* current = root_;
    for(size_t i = 0; i < size_; ++i) {
        if(i == pos) return current->value_;
        else current = current->next_;
    }
    throw std::out_of_range("You are out of list");
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator =(DoubleList& other) {
    clear();
    if(!other.root_) {
        root_ = NULL;
        tail_ = NULL;
        size_ = 0;
    }
    else {
        root_ = new NodeDL<T>(other.root_->value_, other.root_->next_, other.root_->prev_);
        NodeDL<T>* current = root_;

        while(current->next_ != nullptr) {
            NodeDL<T>* new_node = new NodeDL<T>(current->next_->value_, current->next_->next_, current);
            current->next_ = new_node;
            current = new_node;
        }

        tail_ = current;
        size_ = other.size_;
    }

    return  *this;
}

template<typename T>
DoubleList<T>& DoubleList<T>::operator =(DoubleList&& other) {
    root_ = other.root_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.tail_ = nullptr;
    return *this;
}

// template<typename T>
// T& DoubleList<T>::at(size_t n)
// {
//     if(data_begin_ + n >= data_begin_ + size_) throw std::out_of_range("You're out of the DoubleList");
//     return *(data_begin_ + n);
// }

template<typename T>
void DoubleList<T>::push_back(T value) {
    NodeDL<T>* node = new NodeDL<T>(value, nullptr, nullptr);
    if(!root_) {
        root_ = node;
        tail_ = node;
        ++size_;
    }
    else {
        node->prev_ = tail_;
        tail_->next_ = node;
        tail_ = node;
        ++size_;
    }
}

template<typename T>
void DoubleList<T>::insert(T value, size_t pos) {
    if(pos > size_) throw std::out_of_range("You're out of the DoubleList");
    else if(pos == size_) push_back(value);
    else if(pos == 0) {
        NodeDL<T>* new_node = new NodeDL<T>(value, root_, nullptr);
        root_->prev_ = new_node;
        root_ = root_->prev_;
        ++size_;
    }
    else {
        size_t i = 0;
        NodeDL<T>* current = root_;
        while(i != pos) {
            current = current->next_;
            ++i;
        }
        NodeDL<T>* new_node = new NodeDL<T>(value, current, current->prev_);
        current->prev_->next_ = new_node;
        current->prev_ = new_node;
        ++size_;
    }
}

template<typename T>
void DoubleList<T>::erase(size_t pos) {
    if(pos >= size_) throw std::out_of_range("You're out of the DoubleList");
    else if(size_ == 1) {
        delete root_;
        root_ = NULL;
        tail_ = NULL;
        size_ = 0;
        return;
    }
    else if(pos == size_ - 1) {
        NodeDL<T>* new_tail = tail_->prev_;
        delete tail_;
        tail_ = new_tail;
        --size_;
    }
    else if(pos == 0) {
        NodeDL<T>* next = root_->next_;
        delete root_;
        root_ = next;
        --size_;
    }
    else {
        size_t i = 0;
        NodeDL<T>* current = root_;
        while(i != pos) {
            current = current->next_;
            ++i;
        }
        current->prev_->next_ = current->next_;
        current->next_->prev_ = current->prev_;
        delete current;
        --size_;
    }
}

template<typename T>
void DoubleList<T>::clear()
{
    if(!root_) return;

    NodeDL<T>* begin = root_;
    NodeDL<T>* next = nullptr;
    while(begin != tail_) {
        next = begin->next_;
        delete begin;
        begin = next;
    }
    delete tail_;

    size_ = 0;
    root_ = nullptr;
    tail_ = nullptr;
}

template<typename T>
size_t DoubleList<T>::size() const
{
    return size_;
}

template<typename T>
void DoubleList<T>::open() const
{      
    NodeDL<T>* current = root_;
    while(current != tail_) {
        std::cout << current->value_ << ' ';
        current = current->next_;
    }
    std::cout << tail_->value_;
}


template<typename T>
typename DoubleList<T>::Iterator DoubleList<T>::begin() {
    return {this, root_};
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
   current_node_ = current_node_->next_;
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