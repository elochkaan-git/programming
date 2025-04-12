#include "mop.hpp"
#include <ostream>

int whoTakeMop(int n = 1, int time = 1) {
    if (time == 0 || n == 1) return 1;
    int reverse = time / (n-1);
    if (reverse % 2 == 0) return 1 + time % (n-1);
    else return n - time % (n-1);
}

int main() {
    std::cout << "Testing function with critical values:\n";
    std::cout << ">>> " << std::flush; test_whoTakeMop_borders(); std::cout << "OK\n";

    std::cout << "Testing function with random values:\n";
    std::cout << ">>> " << std::flush; test_whoTakeMop_random(); std::cout << "OK\n";

    std::cout << "Testing function with incorrect values:\n";
    std::cout << ">>> " << std::flush; test_whoTakeMop_incorrect(); std::cout << "OK\n";

    return 0;
}