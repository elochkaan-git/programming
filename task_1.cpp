#include "hash.hpp"

std::map<std::string, std::string> members;
unsigned long duplicates = 0;

int main() {
    enrolled(".\\members.txt");
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        if(input == "end") {
            end();
            return 0;
        }
        unenrolled(input);
    }
}