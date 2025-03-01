#include "functions.hpp"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int input_1, input_2;
    std::vector<int> result;
    
    // ������� ��������� ����� input_1
    std::cout << "������� ����������� �����, ��������� �������� ������ ������: ";
    std::cin >> input_1;
    if (input_1 < 101) return -1;
    result = factorial(input_1);
    std::cout << "��������� ����� " << input_1 << ": ";
    print_vector(result);

    // ������� 2 � ������� input_1
    std::cout << std::endl << std::endl << "������� ����������� ����� -- �������, � ������� �� ����� ��������� ������: ";
    std::cin >> input_1;
    if (input_1 < 65) return -1;
    result = power2(input_1);
    std::cout << "��� � ������� " << input_1 << ": ";
    print_vector(result);

    // ������� ����� 2 � �������� input_1 � input_2
    std::cout << std::endl << std::endl << "������� ����������� ����� -- �������, � ������� �� ����� ��������� ������, � ����� ���������� ������������ �����: ";
    std::cin >> input_1 >> input_2;
    if (input_1 < 65 && input_2 < 65) return -1;
    result = long_arithmetic_sum(power2(input_1), power2(input_2));
    std::cout << "2^" << input_1 << " + " << "2^" << input_2 << " = ";
    print_vector(result);

    // ������� �������� 2 � �������� input_1 � input_2
    std::cout << std::endl << std::endl << "������� ����������� ����� -- �������, � ������� �� ����� ��������� ������, � ����� ���������� ������������ ����� (������ ����� ����������� ������ �������!): ";
    std::cin >> input_1 >> input_2;
    if (input_1 < 65 && input_2 < 65) return -1;
    result = long_arithmetic_minus(power2(input_1), power2(input_2));
    std::cout << "2^" << input_1 << " - " << "2^" << input_2 << " = ";
    print_vector(result);

    // ������� n-�� ����� ���������
    std::cout << std::endl << std::endl << "������� ����� ����� � ������������������ ���������: ";
    std::cin >> input_1;
    if (input_1 < 101) return -1;
    result = fibonacci(input_1);
    std::cout << input_1 << " ����� � ������������������ ���������: ";
    print_vector(result);
}