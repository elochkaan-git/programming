#include "bundle.hpp"

void five() {
    std::cout << "Executing function five():\n";
    std::cout << "\tMUAHHAHAA, I'M GONNA RAISE AN ERROR!!! >:)\n\n";
    throw 3.141;
    std::cout << "1234567890\n\n";
}

void four() {
    std::cout << "Executing function four():\n";
    std::cout << "\tI'm useless function, here just to say that :(\n\n";
    five();
    std::cout << "1234567890\n\n";
}

void three() {
    try{
        std::cout << "Executing function three():\n";
        std::cout << '\t';
        for (int i = 0; i < 256; i += 2) std::cout << i << ' ';
        std::cout << "\n\n";
        four();
    }
    catch (int e) {
        std::cout << "CRITICAL ERROR:\n";
        std::cout << "\tOopsie, an error occured in function three(), 'cos int\n";
    }
    std::cout << "1234567890\n\n";
}

void two() {
    try{
        std::cout << "Executing function two():\n";
        std::cout << "\tI'm printing some words!\n\n";
        three();
    }
    catch (int e) {
        std::cout << "CRITICAL ERROR:\n";
        std::cout << "\tOopsie, an error occured in function two(), 'cos int\n";
    }
    catch (double e) {
        std::cout << "CRITICAL ERROR:\n";
        std::cout << "\tOopsie, an error occured in function two(), 'cos double\n";
    }
    std::cout << "1234567890\n\n";
}

void one() {
    std::cout << "Executing function one():\n";
    std::cout << "\tJust doing + operations: " << 1 << " + " << 2 << " = " << 1+2 << "\n\n";
    two();
}