//
// Created by Oleg on 6/27/2018.
//

#include "matrix.h"
#include "neural_matrix.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

// this operator will be used when creating error vectors through back-propogation
/*
template <typename T, class O>
Matrix<T>::Matrix(const O& other, bool using_data) :
        N(other.N), M(other.M), matrix(other.N, std::vector<long double>(other.M)) {
    register size_t i, j;
    if(using_data) {
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                matrix[i][j] = other.matrix[i][j] -> data;
            }
        }
    } else {
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                matrix[i][j] = other.matrix[i][j] -> function;
            }
        }
    }
}*/

/*
 * for operators between the elementary long double matrices and the neural matrices,
 * the field accessed from the neural matrix will always be the 'data' field, with the
 * exception of the multiplication operator
 */


Matrix<long double>* matrix_subtraction(Matrix<long double>* first, const NeuralMatrix *second) const {
    if(first -> equal_size(*second)) {
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

Matrix<long double>* hadamard_product(Matrix<long double>* first, const NeuralMatrix *other) const {
    if(first -> equal_size(*other)) {
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
template <>
Matrix<long double>* matrix_multiplication(const Matrix<long double>* first, const NeuralMatrix* other) const {
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


template <>
Matrix<long double>* matrix_add(const Matrix<long double>* first, const NeuralMatrix* other) const {
    if(first -> equal_size(*other)) {
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