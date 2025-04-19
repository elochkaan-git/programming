#include "store.hpp"

int main() {
    unsigned int choice = 0;
    HashTable magazine;

    while(choice != 6) {
        std::cout << "What do you want to do?\n1. Insert\n2. Remove\n3. Find\n4. Get size\n5. Check if table empty\n6. Exit\n\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "How many items? "; std::cin >> choice;
            std::string name; unsigned long long price;
            std::cout << "Enter the name and price in each line:\n";
            for(unsigned int t = 0; t < choice; t++) {
                std::cin >> name >> price;
                magazine.insert(name, price);   
            }
            std::cout << '\n';
        }
            
        if (choice == 2) {
            std::string name;
            std::cout << "Enter the name of item that you want to delete: ";
            std::cin >> name; std::cout << '\n';
            magazine.remove(name);
        }

        if(choice == 3) {
            std::string name;
            std::cout << "Which item's price do you want to know: ";
            std::cin >> name;
            if (magazine.find(name) == 0) std::cout << "No such item!\n\n";
            else std::cout << "The price of " << name << " is " << magazine.find(name) << " robuxes\n\n";
        }

        if(choice == 4) {
            std::cout << "Amount of products is " << magazine.size() << "\n\n";
        }

        if(choice == 5) {
            std::cout << "Is store empty? ";
            if(magazine.is_empty()) std::cout << "Yes\n\n";
            else std::cout << "No\n\n";
        }
    }

    return 0;
}