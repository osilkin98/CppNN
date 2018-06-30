//
// Created by Oleg on 6/29/2018.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

//
// Created by Oleg on 6/27/2018.
//

#include "matrix.h"
#include "neural_matrix.h"

#include "matrix_operators.h"


Matrix<long double>* matrix_operators::subtract(const Matrix<long double>* first, const NeuralMatrix *second) {
    if(first -> N == second -> N && first -> M == second -> M) {
        Matrix<long double> *difference = new Matrix<long double>(first -> N, second -> M);
        if(difference == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = first -> matrix[i][j] - second -> matrix[i][j] -> data;
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

Matrix<long double>* matrix_operators::hadamard_product(const Matrix<long double>* first, const NeuralMatrix *other)  {
    if(first -> N == other -> N && first -> M == other -> M) {
        Matrix<long double> *product = new Matrix<long double>(first -> N, first -> M);
        if(product == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                product -> matrix[i][j] = first -> matrix[i][j] - other -> matrix[i][j] -> data;
            }
        }
        return product;
    } else {
        throw std::length_error("Dimensions mismatch");
    }
}


// there's likely a better way to do these multiplications than to write specific cases for the matrices
// using something like iterators for data members and then just iterating through and returning a vector of
// doubles which is the resuult of whatever multiplicatios
Matrix<long double>* matrix_operators::multiply(const Matrix<long double> *first, const NeuralMatrix *other)  {
    if(first -> M == other -> N) {
        Matrix<long double> *product = new Matrix<long double>(first -> N, other -> M);
        if(product == nullptr) {
            return nullptr;
        }
        register size_t i, j, k;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < other -> M; ++j) {
                product -> matrix[i][j] = 0;
                for(k = 0; k < first -> M; ++k) {
                    product -> matrix[i][j] += first -> matrix[i][k] * other -> matrix[k][j] -> function;
                }
            }
        }
        return product;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

Matrix<long double>* matrix_operators::multiply(const NeuralMatrix* first, const Matrix<long double>* other)  {
    if(first -> M == other -> N) {
        Matrix<long double> *product = new Matrix<long double>(first -> N, other -> M);
        if(product == nullptr) {
            return nullptr;
        }
        register size_t i, j, k;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < other -> M; ++j) {
                product -> matrix[i][j] = 0;
                for(k = 0; k < first -> M; ++k) {
                    product -> matrix[i][j] += first -> matrix[i][k] -> function * other -> matrix[k][j];
                }
            }
        }
        return product;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}


Matrix<long double>* matrix_operators::add(const Matrix<long double>* first, const NeuralMatrix* other) {
    if(first -> N == other -> N && first -> M == other -> M) {
        Matrix<long double> *difference = new Matrix<long double>(first -> N, first -> M);
        if(difference == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = first -> matrix[i][j] - other -> matrix[i][j] -> data;
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

#pragma clang diagnostic pop