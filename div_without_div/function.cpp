#include "div.hpp"

long long division_without_division(signed int a, signed int b) {
    bool is_negative = false;

    if (a > 0 and b > 0) is_negative = false;
    else if (a < 0 and b < 0) is_negative = false;
    else is_negative = true;

    unsigned int r = abs(a);
    long long result = 0;
    while (r >= abs(b)) {
        r += (~abs(b)+1);
        result++;
    }

    return (is_negative ? (~result+1) : result);
}