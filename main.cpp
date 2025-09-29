#include <iostream>
#include "Box.hpp"
#include "List.hpp"
#include "DoubleList.hpp"


int main() {
    Box<int> box;
    for(int i = 0; i < 10; ++i) box.push_back(i);
    box.open(); std::cout << '\n';
    std::cout << box.size() << '\n';
    box.erase(6);
    box.erase(4);
    box.erase(2);
    box.open(); std::cout << '\n';
    box.insert(10, 0);
    box.open(); std::cout << '\n';
    box.insert(20, box.size()/2);
    box.open(); std::cout << '\n';
    box.insert(30, box.size());
    box.open(); std::cout << '\n';

    List<int> list;
    for(int i = 0; i < 10; ++i) list.push_back(i);
    list.open(); std::cout << '\n';
    std::cout << list.size() << '\n';
    list.erase(6);
    list.erase(4);
    list.erase(2);
    list.open(); std::cout << '\n';
    list.insert(10, 0);
    list.open(); std::cout << '\n';
    list.insert(20, list.size()/2);
    list.open(); std::cout << '\n';
    list.insert(30, list.size());
    list.open(); std::cout << '\n';

    DoubleList<int> dlist;
    for(int i = 0; i < 10; ++i) dlist.push_back(i);
    dlist.open(); std::cout << '\n';
    std::cout << dlist.size() << '\n';
    dlist.erase(6);
    dlist.erase(4);
    dlist.erase(2);
    dlist.open(); std::cout << '\n';
    dlist.insert(10, 0);
    dlist.open(); std::cout << '\n';
    dlist.insert(20, dlist.size()/2);
    dlist.open(); std::cout << '\n';
    dlist.insert(30, dlist.size());
    dlist.open(); std::cout << '\n';

    return 0;
}