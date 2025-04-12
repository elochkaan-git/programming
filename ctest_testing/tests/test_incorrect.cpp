#include "../walk.hpp"

void test_incorrect() {
    assert(!can_walk(0, 0, 5, 5, 4));
}

int main() {
    test_incorrect();
}