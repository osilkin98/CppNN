#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>
#include <cstddef>
#include <iostream>

template <typename T>
class Matrix {
public:
    std::vector< std::vector<T> > matrix;
    size_t N, M;

    const bool valid(void) const { return N && M; }


    const bool equal_size(const Matrix<T>* other) const {
        return other -> N == N && other -> M == M;
    }

    // operator for matrix multiplication
    Matrix<T>* operator*(Matrix<T>* other) const;

    Matrix<T>* hadamard_product(Matrix<T>* other) const;

    Matrix<T>* operator+(Matrix<T>* other) const;

    Matrix<T>* operator-(Matrix<T>* other) const;

    // for transposing other matrices
    Matrix<T> *transpose(Matrix<T>* other) const;

    // for transposing this matrix
    Matrix<T> *transpose(void);



    Matrix(void) : N(1), M(1), matrix(N, std::vector<T>(M)) { }

    explicit Matrix(const size_t n, const size_t m = 1) : matrix(n, std::vector<T>(m)), N(n), M(m) { }

    // for copying Matrix objects
    Matrix(const Matrix<T>& other) : matrix(other.matrix), N(other.N), M(other.M) { }

    void zero_matrix(void);

    virtual ~Matrix(void) = default;

    virtual void print(void) const;
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

template <typename T>
Matrix<T> *Matrix<T>::transpose(Matrix<T>* other) const {
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
Matrix<T>* Matrix<T>::transpose(void) {
    std::vector< std::vector<T> > temp_vector(M, std::vector<T>(N));
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            temp_vector[j][i] = matrix[i][j];
        }
    }
    N = temp_vector.size();
    M = temp_vector[0].size();
    matrix = temp_vector;
}

template <typename T>
Matrix<T>* Matrix<T>::operator+(Matrix<T>* other) const {
    if(this -> equal_size(other)) {
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
Matrix<T>* Matrix<T>::operator-(Matrix<T>* other) const {
    if(this -> equal_size(other)) {
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
Matrix<T>* Matrix<T>::hadamard_product(Matrix<T>* other) const {
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
Matrix<T>* Matrix<T>::operator*(Matrix<T> *other) const {
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
                    C -> matrix[i][j] += matrix[i][k] * matrix[k][j];
                }
            }
        }
        return C;

    } else {
        return nullptr;
    }
}


template <typename T>
void Matrix<T>::zero_matrix(void) {
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
void Matrix<T>::print(void) const {
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







#endif //NEURALNETWORKS_LINEAR_ALGEBRA_H
#pragma clang diagnostic pop