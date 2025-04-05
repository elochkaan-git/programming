#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

class BaseMatrix {
    protected:
        std::vector<std::vector<int>> matrix;
        BaseMatrix(unsigned int, unsigned int, unsigned char);

    public:
        BaseMatrix();
        BaseMatrix(unsigned int, unsigned int);

        void set(std::vector<std::vector<int>>);
        std::vector<std::vector<int>> get() const;
        long long getRows() const;
        long long getCols() const;
        int max();

        BaseMatrix operator+(const BaseMatrix&);
        BaseMatrix operator-(const BaseMatrix&);
        BaseMatrix operator*(const BaseMatrix&);
        BaseMatrix operator*(int);
        BaseMatrix& operator=(const BaseMatrix&);
        bool operator==(const BaseMatrix&);
        BaseMatrix transpose();
        friend std::ostream& operator<<(std::ostream&, const BaseMatrix&);
        friend std::istream& operator>>(std::istream&, BaseMatrix&);

        ~BaseMatrix();
};

class SquareMatrix : public BaseMatrix {
    private:
        SquareMatrix(unsigned int rows, unsigned char n) : BaseMatrix(rows, rows, n) {};

    public:
        SquareMatrix() : BaseMatrix() {};
        SquareMatrix(unsigned int rows) : BaseMatrix(rows, rows) {};

        SquareMatrix& operator=(const BaseMatrix&);
        friend std::ostream& operator<<(std::ostream&, const SquareMatrix&);
        friend std::istream& operator>>(std::istream&, SquareMatrix&);
        long long determinant();
        bool isSymmetrical();
        BaseMatrix power(unsigned int);
};

long long inversions(unsigned int*, size_t);

#endif