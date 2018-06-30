//
// Created by Oleg on 6/29/2018.
//

#ifndef NEURALNETWORKS_MATRIX_OPERATORS_H
#define NEURALNETWORKS_MATRIX_OPERATORS_H

#include "neural_matrix.h"

/*
 * we have to use this namespace for operators until I can figure out a better way to manage all of these
 * operations in an intuitive manner
 * */

namespace matrix_operators {
    Matrix<long double> *subtract(Matrix<long double> *first, const NeuralMatrix *second);

    Matrix<long double> *hadamard_product(Matrix<long double> *first, const NeuralMatrix *other);

    Matrix<long double> *multiply(const Matrix<long double> *first, const NeuralMatrix *other);

    Matrix<long double> *multiply(const NeuralMatrix *first, const Matrix<long double> *other);

    Matrix<long double> *add(const Matrix<long double> *first, const NeuralMatrix *other);


};

#endif //NEURALNETWORKS_MATRIX_OPERATORS_H
