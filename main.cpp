#include <iostream>
#include <cmath>

int main() {
    double square_root = 0.0;
    double sum = 0.0;
    double input = 0.0;

    std::cin >> input;

    try {
        if (input == -1.0) {
            throw input;
        }

        if (input < 0) {
            throw "Error: negative number";
        }

        square_root = sqrt(input);
        sum = square_root + 1;
    } 
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        std::cerr << "Returning 1." << std::endl;
        return 1;
    } 
    catch (double input) {
        std::cerr << "I caught -1.0!" << std::endl;
        std::cerr << input << std::endl;
        return 1;
    } 
    catch (...) {
        std::cerr << "Whoops!" << std::endl;
        return 1;
    }

    std::cout << "Result: " << sum;

    return 0;
}