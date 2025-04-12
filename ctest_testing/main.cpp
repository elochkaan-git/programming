#include "walk.hpp"

bool can_walk(int x0, int y0, int x1, int y1, int t) {
    if(std::max(abs(x1-x0), abs(y1-y0)) == t) return true;
    return false;
}

