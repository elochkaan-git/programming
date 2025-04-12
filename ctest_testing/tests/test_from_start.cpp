#include "../walk.hpp"

void test_from_start() {
    assert(can_walk(10, 10, 0, 0, 10));
}

int main() {
    test_from_start();
}