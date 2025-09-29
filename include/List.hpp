#pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <stdexcept>


template<typename T>
struct Node {
    T value_;
    std::unique_ptr<Node<T>> next_;

    Node(T value) : value_(value) , next_(nullptr) {}
};


template<typename T>
class List
{
private:
    std::unique_ptr<Node<T>> root_;
    size_t size_;

public:
    List();
    List(size_t n, T value);
    List(List& copy);
    List(List&& moved);
    ~List() = default;

    T& operator [](size_t pos);
    List& operator =(List& other);
    List& operator =(List&& other);

    void open() const;
    void push_back(T value);
    void insert(T value, size_t pos);
    void erase(size_t pos);
    void clear();
    size_t size() const;

    class Iterator
    {
    private:
        List* list_ptr_;
        Node<T>* current_node_;
    
    public:
        Iterator(List* list, size_t index);

        T& operator *();
        bool operator !=(const List<T>::Iterator& other) const;
        bool operator ==(const List<T>::Iterator& other) const;
        void operator ++();
    };

    Iterator begin();
    Iterator end();
};

template<typename T>
List<T>::List()
    : root_(nullptr)
    , size_(0)
{
}

template<typename T>
List<T>::List(size_t n, T value)
    : root_(std::make_unique<Node<T>>(value))
    , size_(n)
{
    for(size_t i = 1; i < n; ++i) {
        push_back(value);
    }
    size_ -= n - 1;
}

template<typename T>
List<T>::List(List& copy)
{
    if(!copy.root_) {
        root_ = nullptr;
        size_ = 0;
        return;
    }
    else {
        root_ = std::make_unique<Node<T>>(copy.root_->value_);
        Node<T>* _this = root_.get();
        Node<T>* _copy = copy.root_.get();

        while(_copy->next_) {
            _this->next_ = std::make_unique<Node<T>>(_copy->next_->value_);
            _this = _this->next_.get();
            _copy = _copy->next_.get();
        }

        size_ = copy.size_;
    }
}

template<typename T>
List<T>::List(List&& moved)
{
    root_ = std::move(moved.root_);
    size_ = moved.size_;
    moved.size_ = 0;
}

template<typename T>
T& List<T>::operator[](size_t pos)
{
    Node<T>* current = root_.get();
    for(size_t i = 0; i < size_; ++i) {
        if(i == pos) return current->value_;
        else current = current->next_.get();
    }
    throw std::out_of_range("You are out of list");
}

template<typename T>
List<T>& List<T>::operator =(List& other) {
    clear();
    if(!other.root_) {
        root_ = nullptr;
        size_ = 0;
    }
    else {
        root_ = std::make_unique<Node<T>>(other.root_->value_);
        Node<T>* _this = root_.get();
        Node<T>* _copy = other.root_.get();

       while(_copy->next_) {
            _this->next_ = std::make_unique<Node<T>>(_copy->next_->value_);
            _this = _this->next_.get();
            _copy = _copy->next_.get();
        }

        size_ = other.size_;
    }

    return  *this;
}

template<typename T>
List<T>& List<T>::operator =(List&& other)
{
    root_ = std::move(other.root_);
    size_ = other.size_;
    other.size_ = 0;

    return *this;
}

template<typename T>
void List<T>::push_back(T value)
{
    if(!root_) {
        root_ = std::make_unique<Node<T>>(value);
    }
    else {
        Node<T>* last = root_.get();
        while (last->next_) last = last->next_.get();
        last->next_ = std::make_unique<Node<T>>(value);
    }
    ++size_;
}

template<typename T>
void List<T>::insert(T value, size_t pos)
{
    if(pos > size_) throw std::out_of_range("You're out of the List");
    else if(pos == size_) push_back(value);
    else if(pos == 0) {
        std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
        new_node->next_ = std::move(root_);
        root_ = std::move(new_node);
        ++size_;
    }
    else {
        size_t i = 0;
        Node<T>* current = root_.get();
        Node<T>* previous = nullptr;
        while(i != pos) {
            previous = current;
            current = current->next_.get();
            ++i;
        }
        std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
        new_node->next_ = std::move(previous->next_);
        previous->next_ = std::move(new_node);
        ++size_;
    }
}

template<typename T>
void List<T>::erase(size_t pos) {
    if(pos >= size_) throw std::out_of_range("You're out of the List");
    else if(pos == 0) {
        root_ = std::move(root_->next_);
    }
    else {
        size_t i = 0;
        Node<T>* current = root_.get();
        Node<T>* previous = nullptr;
        while(i != pos) {
            previous = current;
            current = current->next_.get();
            ++i;
        }
        previous->next_ = std::move(current->next_);
    }
    --size_;
}

template<typename T>
void List<T>::clear()
{
    root_.reset();
    size_ = 0;
}

template<typename T>
size_t List<T>::size() const
{
    return size_;
}

template<typename T>
void List<T>::open() const
{      
    Node<T>* current = root_.get();
    for(size_t i = 0; i < size_; ++i) {
        std::cout << current->value_ << ' ';
        current = current->next_.get();
    }
}


template<typename T>
typename List<T>::Iterator List<T>::begin()
{
    return {this, 0};
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
    return {this, size_};
}


template<typename T>
List<T>::Iterator::Iterator(List<T>* list, size_t index)
{
    list_ptr_ = list;
    
    size_t i = 0;
    current_node_ = list->root_.get();
    while(i != index) {
        current_node_ = current_node_->next_.get();
        ++i;
    }
}

template<typename T>
T& List<T>::Iterator::operator*()
{
    return current_node_->value_;
}

template<typename T>
bool List<T>::Iterator::operator !=(const List<T>::Iterator& other) const
{
    return current_node_ != other.current_node_;
}

template<typename T>
bool List<T>::Iterator::operator ==(const List<T>::Iterator& other) const
{
    return current_node_ == other.current_node_;
}

template<typename T>
void List<T>::Iterator::operator ++()
{
   current_node_ = current_node_->next_.get();
}