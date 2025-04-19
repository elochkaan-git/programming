#include "store.hpp"

int main() {
    HashTable magazine;

    magazine.insert("Apple", 100);
    magazine.insert("Banana", 200);
    magazine.insert("Orange", 300);
    magazine.insert("Milk", 100);
    
    std::cout << "Cost of Milk is "       << magazine.find("Milk") << " emeralds\n";
    std::cout << "Amount of products is " << magazine.size() << '\n';
    std::cout << "Is store empty? "       << magazine.is_empty() << "\n\n\n";

    magazine.remove("Milk");
    magazine.remove("Banana");
    magazine.remove("Apple");
    magazine.remove("Orange");

    std::cout << "Cost of Orange is "     << magazine.find("Orange") << " emeralds\n";
    std::cout << "Amount of products is " << magazine.size() << '\n';
    std::cout << "Is store empty? "       << magazine.is_empty();

    return 0;
}