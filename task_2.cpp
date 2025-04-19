#include "store.hpp"

int main() {
    HashTable magazine(3);
    magazine.insert("Apple", 100);
    magazine.insert("Banana", 200);
    magazine.insert("Orange", 300);
    magazine.insert("Milk", 100);
    
    std::cout << magazine.find("Milk") << '\n';
    std::cout << magazine.size() << '\n';
    std::cout << magazine.is_empty() << '\n';

    magazine.remove("Milk");
    magazine.remove("Banana");
    magazine.remove("Apple");
    magazine.remove("Orange");

    std::cout << magazine.find("Orange") << '\n';
    std::cout << magazine.size() << '\n';
    std::cout << magazine.is_empty();

    return 0;
}