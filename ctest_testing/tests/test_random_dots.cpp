#include "../walk.hpp"

void test_random_dots() {
    assert(can_walk(10, 10, 11, 14, 4));
}

int main() {
    test_random_dots();
}