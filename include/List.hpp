#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>


template<typename T>
struct Node {
    T value_;
    Node* next_;

    Node(T value, Node* next) {
        value_ = value;
        next_ = next;
    }
};


template<typename T>
class List
{
private:
    Node<T>* root_ = nullptr;
    size_t size_ = 0;

public:
    List();
    List(size_t n, T value);
    List(List& copy);
    List(List&& moved);
    ~List();

    T& operator [](size_t pos);
    List& operator =(List& other);
    List& operator =(List&& other);

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
        List* list_ptr_ = nullptr;
        Node<T>* current_node_ = 0;
    
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
List<T>::List() {
    root_ = NULL;
    size_ = 0;
}

template<typename T>
List<T>::List(size_t n, T value) {
    root_ = new Node<T>(value, nullptr);
    Node<T>* current = root_;

    for(size_t i = 1; i < n; ++i) {  // ← i = 1
        Node<T>* leaf = new Node<T>(value, nullptr);
        current->next_ = leaf;
        current = leaf;
    }
    size_ = n;
}

template<typename T>
List<T>::List(List& copy) {
    if(!copy.root_) {
        root_ = nullptr;
        size_ = 0;
        return;
    }
    else {
        root_ = new Node<T>(copy.root_->value_, copy.root_->next_);
        Node<T>* current = root_;

        while(current->next_ != nullptr) {
            Node<T>* new_node = new Node<T>(current->next_->value_, current->next_->next_);
            current->next_ = new_node;
            current = new_node;
        }

        size_ = copy.size_;
    }
}

template<typename T>
List<T>::List(List&& moved) {
    root_ = moved.root_;
    size_ = moved.size_;
    moved.root_ = nullptr;
}

template<typename T>
List<T>::~List() {
    if(!root_) return;

    Node<T>* begin = root_;
    Node<T>* next = nullptr;
    while(begin != nullptr) {
        next = begin->next_;
        delete begin;
        begin = next;
    }
}

template<typename T>
T& List<T>::operator[](size_t pos) {
    Node<T>* current = root_;
    for(size_t i = 0; i < size_; ++i) {
        if(i == pos) return current->value_;
        else current = current->next_;
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
        root_ = new Node<T>(other.root_->value_, other.root_->next_);
        Node<T>* current = root_;

        while(current->next_ != nullptr) {
            Node<T>* new_node = new Node<T>(current->next_->value_, current->next_->next_);
            current->next_ = new_node;
            current = new_node;
        }

        size_ = other.size_;
    }

    return  *this;
}

template<typename T>
List<T>& List<T>::operator =(List&& other) {
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    return *this;
}

// template<typename T>
// T& List<T>::at(size_t n)
// {
//     if(data_begin_ + n >= data_begin_ + size_) throw std::out_of_range("You're out of the List");
//     return *(data_begin_ + n);
// }

template<typename T>
void List<T>::push_back(T value) {
    Node<T>* last = nullptr;
    if(!root_) {
        root_ = new Node<T>(value, nullptr);
        ++size_;
        return;
    }
    last = root_;

    while (last->next_ != nullptr) last = last->next_;
    Node<T>* new_node = new Node<T>(value, nullptr);
    last->next_ = new_node;
    ++size_;
}

template<typename T>
void List<T>::insert(T value, size_t pos) {
    if(pos > size_) throw std::out_of_range("You're out of the List");
    else if(pos == size_) push_back(value);
    else if(pos == 0) {
        Node<T>* new_node = new Node<T>(value, root_);
        root_ = new_node;
        ++size_;
    }
    else {
        size_t i = 0;
        Node<T>* current = root_;
        Node<T>* previous = nullptr;
        while(i != pos) {
            previous = current;
            current = current->next_;
            ++i;
        }
        Node<T>* new_node = new Node<T>(value, current);
        previous->next_ = new_node;
        ++size_;
    }
}

template<typename T>
void List<T>::erase(size_t pos) {
    if(pos >= size_) throw std::out_of_range("You're out of the List");
    else if(pos == 0) {
        Node<T>* next = root_->next_;
        delete root_;
        root_ = next;
        --size_;
    }
    else {
        size_t i = 0;
        Node<T>* current = root_;
        Node<T>* previous = nullptr;
        while(i != pos) {
            previous = current;
            current = current->next_;
            ++i;
        }
        Node<T>* next = current->next_;
        delete current;
        previous->next_ = next;
        --size_;
    }
}

template<typename T>
void List<T>::clear()
{
    if(!root_) return;

    Node<T>* begin = root_;
    Node<T>* next = nullptr;
    while(begin != nullptr) {
        next = begin->next_;
        delete begin;
        begin = next;
    }

    size_ = 0;
    root_ = nullptr;
}

template<typename T>
size_t List<T>::size() const
{
    return size_;
}

template<typename T>
void List<T>::open() const
{      
    Node<T>* current = root_;
    for(size_t i = 0; i < size_; ++i) {
        std::cout << current->value_ << ' ';
        current = current->next_;
    }
}


template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return {this, 0};
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return {this, size_};
}


template<typename T>
List<T>::Iterator::Iterator(List<T>* list, size_t index) {
    list_ptr_ = list;
    
    size_t i = 0;
    current_node_ = list->root_;
    while(i != index) {
        current_node_ = current_node_->next_;
        ++i;
    }
}

template<typename T>
T& List<T>::Iterator::operator*() {
    return current_node_->value_;
}

template<typename T>
bool List<T>::Iterator::operator !=(const List<T>::Iterator& other) const {
    return current_node_ != other.current_node_;
}

template<typename T>
bool List<T>::Iterator::operator ==(const List<T>::Iterator& other) const {
    return current_node_ == other.current_node_;
}

template<typename T>
void List<T>::Iterator::operator ++() {
   current_node_ = current_node_->next_;
}