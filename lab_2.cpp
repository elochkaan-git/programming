#include "functions.hpp"
#include <vector>

int main() {
    int input_1, input_2;
    std::vector<int> result;
    
    // Считаем факториал числа input_1
    std::cout << "Введите натуральное число, факториал которого хотите ввести: ";
    std::cin >> input_1;
    result = factorial(input_1);
    std::cout << "Факториал числа " << input_1 << ": ";
    print_vector(result);

    // Считаем 2 в степени input_1
    std::cout << std::endl << std::endl << "Введите натуральное число -- степень, в которую мы будем возводить двойку: ";
    std::cin >> input_1;
    result = power2(input_1);
    std::cout << "Два в степени " << input_1 << ": ";
    print_vector(result);

    // Считаем сумма 2 в степенях input_1 и input_2
    std::cout << std::endl << std::endl << "Введите натуральные число -- степени, в которую мы будем возводить двойки, а затем складывать получившиеся числа: ";
    std::cin >> input_1 >> input_2;
    result = long_arithmetic_sum(power2(input_1), power2(input_2));
    std::cout << "2^" << input_1 << " + " << "2^" << input_2 << " = ";
    print_vector(result);

    // Считаем разность 2 в степенях input_1 и input_2
    std::cout << std::endl << std::endl << "Введите натуральные число -- степени, в которую мы будем возводить двойки, а затем складывать получившиеся числа (первое число обязательно больше второго!): ";
    std::cin >> input_1 >> input_2;
    result = long_arithmetic_minus(power2(input_1), power2(input_2));
    std::cout << "Два в степени " << input_1 << " - " << "два в степени " << input_2 << " = ";
    print_vector(result);

    // Считаем n-ое число Фибоначчи
    std::cout << std::endl << std::endl << "Введите номер числа в последовательности Фибоначчи: ";
    std::cin >> input_1;
    result = fibonacci(input_1);
    std::cout << input_1 << " число в последовательности Фибоначчи: ";
    print_vector(result);
}