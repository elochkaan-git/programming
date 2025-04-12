#include "mop.hpp"
#include <cassert>

void test_whoTakeMop_borders() {
    assert(whoTakeMop(1, 100) == 1);
    assert(whoTakeMop(100, 0) == 1);
}

void test_whoTakeMop_random() {
    assert(whoTakeMop(4, 10) == 3);
    assert(whoTakeMop(3, 10) == 3);
    assert(whoTakeMop(100, 100) == 99);
    assert(whoTakeMop(56, 10) == 11);
}

void test_whoTakeMop_incorrect() {
    assert(!(whoTakeMop(1, 0) == 2));
    assert(!(whoTakeMop(10, 10) == 10));
    assert(!(whoTakeMop(3, 1) == 1));
}