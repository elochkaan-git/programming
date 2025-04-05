#include "matrix.hpp"

int main() {
    int k = 0;
    std::cout << "Which matrix you want to test?\n1. Common matrixes\n2. Square matrixes\n\n";
    std::cin >> k;
    
    if (k == 1) {
        BaseMatrix test, tset, result;

        std::cout << "Basic constructor of matrix:\n" << test << '\n';
        std::cout << "Constructor with random numbers:\n" << BaseMatrix(5, 10) << '\n';

        std::cout << "Input matrix (first line - two numbers - size of matrix; next lines - numbers in matrix): ";
        std::cin >> test;
        std::cout << "Input another matrix: ";
        std::cin >> tset; std::cout << '\n';
    
        result = test + tset;
        std::cout << "Sum of matrix:\n" << result << '\n';
        
        result = test - tset;
        std::cout << "Difference between matrix:\n" << result << '\n';
    
        std::cout << "Input first matrix for multiply: ";
        std::cin >> test;
        std::cout << "Input second matrix for multiply: ";
        std::cin >> tset;
    
        result = test * tset;
        std::cout << "Multiplication:\n" << result << '\n';
    
        std::cout << "Enter the number: "; std::cin >> k;
        result = result * k;
        std::cout << "Multiplication matrix and number:\n" << result << '\n';
    
        std::cout << "Max element of matrix is " << result.max() << '\n';
    }
    else if (k == 2) {
        SquareMatrix test, tset, result;

        std::cout << "Basic constructor of square matrix:\n" << test << '\n';
        std::cout << "Constructor with random numbers:\n" << SquareMatrix(10) << '\n';

        std::cout << "Input matrix (first line - two numbers - size of matrix; next lines - numbers in matrix): ";
        std::cin >> test;
        std::cout << "Input another matrix: ";
        std::cin >> tset; std::cout << '\n';

        result = test + tset;
        std::cout << "Sum of matrix:\n" << result << '\n';

        result = test - tset;
        std::cout << "Difference between matrix:\n" << result << '\n';

        std::cout << "Input first matrix for multiply: ";
        std::cin >> test;
        std::cout << "Input second matrix for multiply: ";
        std::cin >> tset;

        result = test * tset;
        std::cout << "Multiplication:\n" << result << '\n';

        std::cout << "Enter the number: "; std::cin >> k;
        result = result * k;
        std::cout << "Multiplication matrix and number:\n" << result << '\n';

        std::cout << "Max element of matrix is " << result.max() << '\n';
        std::cout << "Determinant of matrix is " << result.determinant() << '\n';
        std::cout << "Is matrix symmetrical? " << result.isSymmetrical() << "\n\n";

        std::cout << "Enter the power >= 1. Power may be only the natural numbers: ";
        std::cin >> k;
        std::cout << "Matrix in power " << k << ":\n" << result.power(10);
    }
    else {
        std::cerr << "Incorrect choice! Shutdown programm..."; return -2;
    }

    return 0;
}