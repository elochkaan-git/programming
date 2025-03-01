#include "functions.hpp"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int input_1, input_2;
    std::vector<int> result;
    
    // —читаем факториал числа input_1
    std::cout << "¬ведите натуральное число, факториал которого хотите ввести: ";
    std::cin >> input_1;
    if (input_1 < 101) return -1;
    result = factorial(input_1);
    std::cout << "‘акториал числа " << input_1 << ": ";
    print_vector(result);

    // —читаем 2 в степени input_1
    std::cout << std::endl << std::endl << "¬ведите натуральное число -- степень, в которую мы будем возводить двойку: ";
    std::cin >> input_1;
    if (input_1 < 65) return -1;
    result = power2(input_1);
    std::cout << "ƒва в степени " << input_1 << ": ";
    print_vector(result);

    // —читаем сумма 2 в степен€х input_1 и input_2
    std::cout << std::endl << std::endl << "¬ведите натуральные число -- степени, в которую мы будем возводить двойки, а затем складывать получившиес€ числа: ";
    std::cin >> input_1 >> input_2;
    if (input_1 < 65 && input_2 < 65) return -1;
    result = long_arithmetic_sum(power2(input_1), power2(input_2));
    std::cout << "2^" << input_1 << " + " << "2^" << input_2 << " = ";
    print_vector(result);

    // —читаем разность 2 в степен€х input_1 и input_2
    std::cout << std::endl << std::endl << "¬ведите натуральные число -- степени, в которую мы будем возводить двойки, а затем складывать получившиес€ числа (первое число об€зательно больше второго!): ";
    std::cin >> input_1 >> input_2;
    if (input_1 < 65 && input_2 < 65) return -1;
    result = long_arithmetic_minus(power2(input_1), power2(input_2));
    std::cout << "2^" << input_1 << " - " << "2^" << input_2 << " = ";
    print_vector(result);

    // —читаем n-ое число ‘ибоначчи
    std::cout << std::endl << std::endl << "¬ведите номер числа в последовательности ‘ибоначчи: ";
    std::cin >> input_1;
    if (input_1 < 101) return -1;
    result = fibonacci(input_1);
    std::cout << input_1 << " число в последовательности ‘ибоначчи: ";
    print_vector(result);
}