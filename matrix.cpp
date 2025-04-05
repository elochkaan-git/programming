#include "matrix.hpp"

/*
-- METHODS OF BaseMatrix --
*/

BaseMatrix::BaseMatrix() {
    matrix = {{0, 0}, {0, 0}};
}

BaseMatrix::BaseMatrix(unsigned int r, unsigned int c) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::srand(std::time(0));

    matrix.resize(r);
    for (unsigned int i = 0; i < matrix.size(); ++i) matrix[i].resize(c);

    for (unsigned int i = 0; i < r; ++i)
        for (unsigned int j = 0; j < c; ++j)
            matrix[i][j] = rand() % 10;
}

BaseMatrix::BaseMatrix(unsigned int r, unsigned int c, unsigned char n) {
    matrix.resize(r);
    for (unsigned int i = 0; i < matrix.size(); ++i) matrix[i].resize(c);

    for (unsigned int i = 0; i < r; ++i)
        for (unsigned int j = 0; j < c; ++j)
            matrix[i][j] = n;
}

void BaseMatrix::set(std::vector<std::vector<int>> m) { matrix = m; }

std::vector<std::vector<int>> BaseMatrix::get() const { return matrix; }

long long BaseMatrix::getRows() const { return matrix.size(); }

long long BaseMatrix::getCols() const { return matrix[0].size(); }

int BaseMatrix::max() {
    int maximum = INT_MIN;

    for (std::vector<int> cols : matrix)
        for (int el : cols)
            if (el > maximum ) maximum = el;

    return maximum;
}

BaseMatrix BaseMatrix::operator+(const BaseMatrix& other) {
    if (this->getRows() == other.getRows() && this->getCols() == other.getCols()) {
        unsigned int rows = this->getRows(), cols = this->getCols();
        BaseMatrix temp(rows, cols, 0);

        for (unsigned int i = 0; i < rows; ++i)
            for (unsigned int j = 0; j < cols; ++j)
                temp.matrix[i][j] = matrix[i][j] + other.matrix[i][j];

        return temp;
    }
    else { std::cerr << "Wrong sizes!"; exit(-1);}
}

BaseMatrix BaseMatrix::operator-(const BaseMatrix& other) {
    if (this->getRows() == other.getRows() && this->getCols() == other.getCols()) {
        unsigned int rows = matrix.size(), cols = matrix[0].size();
        BaseMatrix temp(rows, cols, 0);

        for (unsigned int i = 0; i < rows; ++i)
            for (unsigned int j = 0; j < cols; ++j)
                temp.matrix[i][j] = matrix[i][j] - other.matrix[i][j];

        return temp;
    }
    else { std::cerr << "Wrong sizes!"; exit(-1);}
}

BaseMatrix BaseMatrix::operator*(const BaseMatrix& other) {
    if (this->getRows() == other.getCols() && this->getCols() == other.getRows()) {
        unsigned int rows = matrix.size(), cols = other.matrix[0].size();
        BaseMatrix temp(rows, cols, 0);

        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                temp.matrix[i][j] = 0;
                for (unsigned int k = 0; k < matrix[0].size(); ++k)
                    temp.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
        
        return temp;
    }
    else { std::cerr << "Wrong sizes!"; exit(-1);}
}

BaseMatrix BaseMatrix::operator*(int k) {
    unsigned int rows = this->getRows(), cols = this->getCols();
    BaseMatrix temp(rows, cols, 0);

    for (unsigned int i = 0; i < rows; ++i)
        for (unsigned int j = 0; j < cols; ++j)
            temp.matrix[i][j] = matrix[i][j] * k;

    return temp;
}

BaseMatrix& BaseMatrix::operator=(const BaseMatrix& other) {
    if (this != &other) matrix = other.matrix;
    return *this;
}

bool BaseMatrix::operator==(const BaseMatrix& other) {
    if (this->getRows() == other.getRows() && this->getCols() == other.getCols()) {
        if (matrix == other.matrix) return true;
        return false;
    }
    else { std::cerr << "Wrong sizes!"; exit(-1);}
}

BaseMatrix BaseMatrix::transpose() {
    long long rows = this->getRows(), cols = this->getCols();
    BaseMatrix temp(cols, rows, 0);

    for (long long i = 0; i < rows; ++i)
        for (long long j = 0; j < cols; ++j)
            temp.matrix[j][i] = matrix[i][j];

    return temp;
}

std::ostream& operator<<(std::ostream& stream, const BaseMatrix& Matrix) {   
    for (unsigned int i = 0; i < Matrix.getRows(); ++i) {
        for (unsigned int j = 0; j < Matrix.getCols(); ++j)
            stream << Matrix.matrix[i][j] << ' ';
        stream << '\n';
    }
    
    return stream;
}

std::istream& operator>>(std::istream& stream, BaseMatrix& Matrix) {
    unsigned int rows = 0, cols = 0;
    stream >> rows >> cols;
    
    Matrix = BaseMatrix(rows, cols, 0);

    for (unsigned int i = 0; i < rows; ++i) 
        for (unsigned int j = 0; j < cols; ++j)
            stream >> Matrix.matrix[i][j];
    
    return stream;
}

BaseMatrix::~BaseMatrix() {};

/*
-- METHODS OF SquareMatrix --
*/

SquareMatrix& SquareMatrix::operator=(const BaseMatrix& other) {
    if (other.getRows() == other.getCols())
        if (this != &other) (*this).set(other.get());
    else {
        std::cerr << "Right matrix is not square!"; exit(-1);
    }
    return *this;
}

long long SquareMatrix::determinant() {
    unsigned int indexes[getRows()] {};
    for (unsigned int i = 0; i < getRows(); ++i) indexes[i] = i+1;
    long long det = 0, temp = 1; char sign = -1;

    do {
        if (inversions(indexes, getRows()) % 2 == 0) sign = 1;
        else sign = -1;

        for (unsigned int i = 0; i < getRows(); ++i) {
            temp *= matrix[i][indexes[i]-1];
        }

        det += sign * temp;
        temp = 1;
    } while (std::next_permutation(indexes, indexes+getRows()));

    return det;
}

bool SquareMatrix::isSymmetrical() {
    if (matrix == this->transpose().get()) return true;
    return false;
}

BaseMatrix SquareMatrix::power(unsigned int k) {
    if (k == 1) return *this;
    else return (*this) * power(k-1);
}

std::ostream& operator<<(std::ostream& stream, const SquareMatrix& Matrix) {   
    for (unsigned int i = 0; i < Matrix.getRows(); ++i) {
        for (unsigned int j = 0; j < Matrix.getCols(); ++j)
            stream << Matrix.matrix[i][j] << ' ';
        stream << '\n';
    }
    
    return stream;
}

std::istream& operator>>(std::istream& stream, SquareMatrix& Matrix) {
    unsigned int rows = 0, cols = 0;
    stream >> rows >> cols;
    
    Matrix = SquareMatrix(rows, 0);

    for (unsigned int i = 0; i < rows; ++i) 
        for (unsigned int j = 0; j < cols; ++j)
            stream >> Matrix.matrix[i][j];
    
    return stream;
}

/*
-- OTHER METHODS
*/

long long inversions(unsigned int* indexes, size_t size) {
    long long inv = 0;
    for (unsigned int i = 0; i < size; ++i)
        for (unsigned int j = i+1; j < size; ++j) {
            unsigned int a = *(indexes + i), b = *(indexes + j);
            if (a > b) inv++;
        }

    return inv;
}
