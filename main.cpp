#include "Box.hpp"
#include <iostream>

int main() {
    Box<int> box;
    for(int i = 0; i < 10; ++i) box.push_back(i);
    box.open();
    std::cout << '\n' << box.size() << '\n';
    box.erase(6);
    box.erase(4);
    box.erase(2);
    box.open(); std::cout << '\n';
    box.insert(10, 0);
    box.open(); std::cout << '\n';
    box.insert(20, 4);
    box.open(); std::cout << '\n';
    box.push_back(30);
    box.open(); std::cout << '\n';

    for(int& n : box) std::cout << n << std::endl;

    return 0;
}