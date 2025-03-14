#include "functions.hpp"

int main() {
    std::vector<std::string> words = {"thanks", "god", "it's", "friday"};
    std::string testCase1 = "tgif", testCase2 = "figt", testCase3 = "never odd or even";

    std::cout << "1 is TRUE, 0 is FALSE!\n\n";

    std::cout << "Is '" << testCase1 << "' anagram of ' ";
    for (std::string word : words) std::cout << word << ' ';
    std::cout << "': " << is_acronim(std::move(testCase1), std::move(words)) << '\n';

    std::cout << "Is '" << testCase2 << "' anagram of ' ";
    for (std::string word : words) std::cout << word << ' ';
    std::cout << "': " << is_acronim(std::move(testCase2), std::move(words)) << '\n';


    std::cout << "Is '" << testCase3 << "' palindrome: " << is_palindrome(std::move(testCase3)) << '\n';


    std::vector<std::string> words_1 = {"bob", "cat", "dog", "bad", "brown"};
    std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::vector<unsigned int> scores = {10,10,10,10,10,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::pair<std::string, unsigned int> result = max_score(std::move(words_1), std::move(letters), std::move(scores));
    std::cout << "Word '"<< result.first << "' have the highest score: " << result.second;
}