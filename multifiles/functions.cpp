#include "functions.hpp"

std::vector<int> number_to_digits(std::string&& number) {
    std::vector<int> storage;
    for(char c : number) storage.push_back(c - '0');
    return storage;
}

void print_vector(std::vector<int>& t) {
    for(int n : t) std::cout << n;
}

std::vector<int> long_arithmetic_multiply(std::vector<int>& one, std::vector<int>& two) {
    std::reverse(one.begin(), one.end());
    std::reverse(two.begin(), two.end());

    std::vector<int> result(one.size() + two.size(), 0);
    for(int i = 0; i < one.size(); ++i) {
        for(int j = 0; j < two.size(); ++j) {
            result[i+j] += one[i] * two[j];
        }
    }

    for(int i = 0; i < result.size()-1; ++i) {
        result[i+1] += result[i] / 10;
        result[i] %= 10;
    }

    if(result[result.size()-1] == 0) { 
        result.pop_back();
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> long_arithmetic_sum(std::vector<int> one, std::vector<int> two) {
    std::reverse(one.begin(), one.end());
    std::reverse(two.begin(), two.end());

    // резервация места
    if (one.size() > two.size()) {
        two.reserve(one.size());
        for (int i = 0; i < one.size() - two.size(); ++i) {
            two.push_back(0);
        }
    }
    else if (one.size() < two.size()) {
        one.reserve(two.size());
        for (int i = 0; i < two.size() - one.size(); ++i) {
            one.push_back(0);
        }
    }

    std::vector<int> result(std::max(one.size(), two.size()) + 1, 0);
    for(int i = 0; i < std::max(one.size(), two.size()); i++) {
        if (one[i] + two[i] + result[i] >= 10) {
            result[i] = (one[i] + two[i] + result[i]) % 10;
            result[i+1] += 1;
        }
        else result[i] += (one[i] + two[i]);
    }

    if(result[result.size()-1] == 0) { 
        result.pop_back();
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> long_arithmetic_minus(std::vector<int> one, std::vector<int> two) {
    std::reverse(one.begin(), one.end());
    std::reverse(two.begin(), two.end());

    if (one == two) return std::vector<int>{0};

    // резервация места
    if (one.size() > two.size()) {
        two.reserve(one.size());
        size_t t = one.size() - two.size();
        for (size_t i = 0; i < t; i++) {
            two.push_back(0);
        }
    }

    std::vector<int> result(one.size(), 0);
    for(int i = 0; i < one.size(); i++) {
        if (one[i] - two[i] < 0) {
            result[i] += (10 + (one[i] - two[i]));
            one[i+1] -= 1;
        }
        else result[i] += (one[i] - two[i]);
    }

    if(result[result.size()-1] == 0) { 
        result.pop_back();
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> factorial(int n) {
    if (n == 1) return std::vector<int>{1};
    else {
        std::vector<int> one = number_to_digits(std::move(std::to_string(n)));
        std::vector<int> temp = factorial(n-1);
        return long_arithmetic_multiply(one, temp);
    }
}

std::vector<int> power2(int n) {
    if (n == 1) return std::vector<int>{2};
    else if (n == 2) return std::vector<int>{4};
    else {
        std::vector<int> one{2};
        std::vector<int> temp = long_arithmetic_multiply(one, one);
        for (int i = 2; i < n; i++) {
            temp = long_arithmetic_multiply(temp, one);
        }
        return temp;
    }
}

std::vector<int> fibonacci(int n) {
    if (n == 1 || n == 2) return std::vector<int>{1};
    else {
        std::vector<int> one {1}; 
        std::vector<int> two {1};
        std::vector<int> temp;

        for (int i = 2; i < n; i++) {
            temp = long_arithmetic_sum(one, two);
            one = two;
            two = temp;
        }

        return two;
    }
}
