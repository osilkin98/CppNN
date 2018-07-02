//
// Created by Oleg on 6/27/2018.
//

#ifndef NEURALNETWORKS_MATRIX_H
#define NEURALNETWORKS_MATRIX_H

#include <vector>
#include <cstddef>
#include <iostream>




template <typename T>
class Matrix {
public:
    std::vector< std::vector<T> > matrix;
    size_t N, M;

    virtual const bool valid() const { return N && M; }


    virtual const bool equal_size(const Matrix<T>& other) const {
        return other.N == N && other.M == M;
    }

    // operator for matrix multiplication
    Matrix<T>* operator*(const Matrix<T>* other) const;

    /// Matrix<long double>* operator*(const NeuralMatrix* other) const;

    Matrix<T>* hadamard_product(const Matrix<T>* other) const;

    // Matrix<long double>* hadamard_product(const NeuralMatrix* other) const;

    Matrix<T>* operator+(const Matrix<T>* other) const;

    // Matrix<long double>* operator+(const NeuralMatrix* other) const;

    Matrix<T>* operator-(const Matrix<T>* other) const;

    Matrix<T>& operator=(const Matrix<T>& other);

    // Matrix<long double>* operator-(const NeuralMatrix* other) const;

    // for transposing other matrices
    static Matrix<T> *transpose(const Matrix<T>* other);

    // for transposing this matrix
    virtual Matrix<T> *transpose() const;



    explicit Matrix() : N(1), M(1), matrix(N, std::vector<T>(M)) { }

    explicit Matrix(const size_t n, const size_t m = 1) : matrix(n, std::vector<T>(m)), N(n), M(m) { }

    // for copying Matrix objects
    Matrix(const Matrix<T>& other) : matrix(other.matrix), N(other.N), M(other.M) { }

    explicit Matrix(const std::vector< std::vector<T> >& other_matrix);


    // the using_data field controls whether we use the data field or function field to create new matrix
    // explicit Matrix<long double>(const NeuralMatrix& other, bool using_data = true);

    // Matrix<long double>(const NeuralMatrix& other, const std::vector<long double>& correct_data);

    void zero_matrix();

    virtual ~Matrix() = default;

    virtual void print() const;
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &other_matrix)
        : N(other_matrix.size()), M(other_matrix.size() ? other_matrix[0].size() : 0), matrix(other_matrix) { }

template <typename T>
Matrix<T> *Matrix<T>::transpose(const Matrix<T>* other) {
    if(!(other -> valid())) {
        return nullptr;
    }

    Matrix<T> *transposed = new Matrix(other -> M, other -> N);

    register size_t i, j;

    for(i = 0; i < other -> N; ++i) {
        for(j = 0; j < other -> M; ++j) {
            transposed -> matrix[j][i] = other -> matrix[i][j];
        }
    }
    return transposed;
}

template <typename T>
Matrix<T>* Matrix<T>::transpose() const {
    std::vector< std::vector<T> > temp_vector(M, std::vector<T>(N));
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            temp_vector[j][i] = matrix[i][j];
        }
    }
    Matrix<T> *to_return = new Matrix<T>(temp_vector);
    return to_return;
}

template <typename T>
Matrix<T>* Matrix<T>::operator+(const Matrix<T>* other) const {
    if(this -> equal_size(*other)) {
        Matrix<T> *C = new Matrix<T>(N, M);
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                C -> matrix[i][j] = matrix[i][j] + other -> matrix[i][j];
            }
        }
        return C;
    }
    return nullptr;
}

template <typename T>
Matrix<T>* Matrix<T>::operator-(const Matrix<T>* other) const {
    if(this -> equal_size(*other)) {
        Matrix<T> *C = new Matrix<T>(N, M);
        if(!C) {
            std::cerr << "Failed to allocate matrix product\n";
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                C -> matrix[i][j] = matrix[i][j] - other -> matrix[i][j];
            }
        }
        return C;
    }
    return nullptr;
}

template <typename T>
Matrix<T>* Matrix<T>::hadamard_product(const Matrix<T>* other) const {
    if(N == other -> N && M == other -> M) {
        Matrix<T> *product = new Matrix(N, M);
        if(!product) {
            std::cerr << "hadamard_product: Failure to allocate new matrix\n";
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                product -> matrix[i][j] = matrix[i][j] * other -> matrix[i][j];
            }
        }
        return product;
    }
    return nullptr;
}


template <typename T>
Matrix<T>* Matrix<T>::operator*(const Matrix<T> *other) const {
    if(M == other -> N) {
        Matrix<T> *C  = new Matrix(N, other -> M);
        if(!C) {
            std::cerr << "Matrix Multiplication: Unable to allocate new matrix product\n";
            return nullptr;
        }
        size_t i, j;
        register size_t k;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < other -> M; ++j) {
                for(k = 0; k < M; ++k) {
                    C -> matrix[i][j] += matrix[i][k] * other -> matrix[k][j]; }
            }
        }
        return C;

    } else {
        return nullptr;
    }
}

/*
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other) {
    if(this != &other) {
        matrix = other.matrix;
        N = other.N;
        M = other.M;
    }
    return *this;
}
*/

template <typename T>
void Matrix<T>::zero_matrix() {
    if(std::is_pointer<T>::value) {
        register size_t i, j;
        for (i = 0; i < N; ++i) {
            for (j = 0; j < M; ++j) {
                delete matrix[i][j];
            }
        }
    }
}


template <typename T>
void Matrix<T>::print() const {
    std::cout << "\n";
    size_t i, j;
    for(i = 0; i < N; ++i) {
        std::cout << "[ ";
        for(j = 0; j < M; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "]\n";
    }
    std::cout << std::endl;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other) {
    if(this != &other) {
        register size_t i;
        for(i = 0; i < N; ++i) {
            matrix[i].clear();
        }
        matrix.clear();
        matrix = other.matrix;
        for(i = 0; i < other.N; ++i) {
            matrix[i] = other.matrix[i];
        }
        N = other.N;
        M = other.M;
    }
    return *this;
}

#endif //NEURALNETWORKS_MATRIX_H
#pragma clang diagnostic pop
