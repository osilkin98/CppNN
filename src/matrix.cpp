//
// Created by Oleg on 6/27/2018.
//

#include "matrix.h"


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