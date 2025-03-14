#include "functions.hpp"
#include <algorithm>

// Проверяет, является ли слово s акронимом для набора слов words
bool is_acronim(std::string&& s, std::vector<std::string>&& words) {
    std::string firstLetters = "";
    for (std::string word : words) firstLetters += word[0];
    if (s == firstLetters) return true;
    return false;
}

// Проверяет, является ли слово (набор слов) палиндромом
bool is_palindrome(std::string&& s) {
    while (s.find(' ') != std::string::npos) {
        s.replace(s.find(' '), 1, "");
    }

    int r = 0, l = s.length()-1;
    while (r < l) {
        if (s[r] == s[l]) {
            r++; l--;
            continue;
        }
        else return false;
    }
    return true;
}

// Считает количество очков для каждого слова из списка words и возвращает максимальное
// значение вместе со словом
std::pair<std::string, unsigned int> max_score(
    std::vector<std::string>&& words,
    std::vector<char>&& letters,
    std::vector<unsigned int>&& score
) {
    std::string resultWord = ""; unsigned int maxScore = 0;
    for (std::string word : words) {
        unsigned int tempScore = 0; bool isAnagram = true;
        for (char ch : word) {
            if (std::count(word.begin(), word.end(), ch) <= std::count(letters.begin(), letters.end(), ch)) {
                tempScore += score[ch - 'a'];
            }
            else {
                isAnagram = false;
            }
        }

        if (isAnagram) {
            if (tempScore > maxScore) {
                resultWord = word;
                maxScore = tempScore;
            }
        }
    }

    return  std::make_pair(resultWord, maxScore);
}