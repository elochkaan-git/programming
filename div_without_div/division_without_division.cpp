#include "div.hpp"

int main() {
    signed int a, b;
    std::cout << "Enter two signed integer (from -2 147 483 648 to 2 147 483 647): ";
    std::cin >> a >> b;

    std::cout << division_without_division(a, b);
}