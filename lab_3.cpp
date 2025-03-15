#include "functions.hpp"

int main() {
    // Инициализируем переменные для проверки первого и второго заданий
    std::vector<std::string> words = {"thanks", "god", "it's", "friday"};
    std::string testCase1 = "tgif", testCase2 = "figt", testCase3 = "never odd or even";

    // Вывод сообщения с примечанием
    std::cout << "1 is TRUE, 0 is FALSE!\n\n";

    // Вывод результата функции
    std::cout << "Is '" << testCase1 << "' acronim of ' ";
    for (std::string word : words) std::cout << word << ' ';
    std::cout << "': " << is_acronim(std::move(testCase1), std::move(words)) << '\n';
    // Та же функция, но с другим словом
    std::cout << "Is '" << testCase2 << "' acronim of ' ";
    for (std::string word : words) std::cout << word << ' ';
    std::cout << "': " << is_acronim(std::move(testCase2), std::move(words)) << "\n\n";

    // Вывод результата функции, проверяющей на палиндромность
    std::cout << "Is '" << testCase3 << "' palindrome: " << is_palindrome(std::move(testCase3)) << "\n\n";

    // Инициализация переменных для третьей задачи, а также проверка функции для этой же задачи
    std::vector<std::string> words_1 = {"hot", "dad", "is", "bad"};
    std::vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::vector<unsigned int> scores = {10,10,10,10,10,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    unsigned int result = max_score(std::move(words_1), std::move(letters), std::move(scores));
    std::cout << "The highest score: " << result;
}