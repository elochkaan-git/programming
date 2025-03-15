#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool is_acronim(std::string&&, std::vector<std::string>&&);
bool is_palindrome(std::string&&);
unsigned int max_score(
    std::vector<std::string>&&,
    std::vector<char>&&,
    std::vector<unsigned int>&&
);