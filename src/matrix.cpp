//
// Created by Oleg on 6/27/2018.
//

#include "matrix.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

// this operator will be used when creating error vectors through back-propogation
Matrix<long double>::Matrix(const NeuralMatrix& other, bool using_data) :
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
}

/*
 * for operators between the elementary long double matrices and the neural matrices,
 * the field accessed from the neural matrix will always be the 'data' field, with the
 * exception of the multiplication operator
 */


template <>
Matrix<long double>* Matrix<long double>::operator-(const NeuralMatrix *other) const {
    if(equal_size(*other)) {
        Matrix<long double> *difference = new Matrix<long double>(N, M);
        if(difference == nullptr) {
            std::cerr << "Allocation failed at " << this << "\n";
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = matrix[i][j] - other -> matrix[i][j] -> data;
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

template <>
Matrix<long double> *Matrix<long double>::hadamard_product(const NeuralMatrix *other) const {
    if(equal_size(*other)) {
        Matrix<long double> *product = new Matrix<long double>(N, M);
        if(product == nullptr) {
            std::cerr << "Allocation failed at " << this << "\n";
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                product -> matrix[i][j] = matrix[i][j] - other -> matrix[i][j] -> data;
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
Matrix<long double>* Matrix<long double>::operator*(const NeuralMatrix* other) const {
    if(M == other -> N) {
        Matrix<long double> *product = new Matrix<long double>(N, other -> M);
        if(product == nullptr) {
            std::cerr << "Allocation failed at " << this << "\n";
            return nullptr;
        }
        register size_t i, j, k;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < other -> M; ++j) {
                product -> matrix[i][j] = 0;
                for(k = 0; k < M; ++k) {
                    product -> matrix[i][j] += matrix[i][k] * other -> matrix[k][j] -> function;
                }
            }
        }
        return product;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}


template <>
Matrix<long double>* Matrix<long double>::operator+(const NeuralMatrix* other) const {
    if(equal_size(*other)) {
        Matrix<long double> *difference = new Matrix<long double>(N, M);
        if(difference == nullptr) {
            std::cerr << "Allocation failed at " << this << "\n";
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = matrix[i][j] - other -> matrix[i][j] -> data;
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

#pragma clang diagnostic pop