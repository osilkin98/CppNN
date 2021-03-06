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
#include <random>
#include <ctime>
#include <chrono>

using namespace neural_networks::utilities;

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

Matrix<long double>* matrix_operators::subtract(const NeuralMatrix *first, const Matrix<long double>* second) {
    if(first -> N == second -> N && first -> M == second -> M) {
        Matrix<long double> *difference = new Matrix<long double>(first -> N, second -> M);
        if(difference == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = first -> matrix[i][j] -> data - second -> matrix[i][j];
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
                product -> matrix[i][j] = first -> matrix[i][j] * other -> matrix[i][j] -> data;
            }
        }
        return product;
    } else {
        throw std::length_error("Dimensions mismatch");
    }
}

Matrix<long double>* matrix_operators::hadamard_product(const NeuralMatrix* first, const Matrix<long double>* other)  {
    if(first -> N == other -> N && first -> M == other -> M) {
        Matrix<long double> *product = new Matrix<long double>(first -> N, first -> M);
        if(product == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                product -> matrix[i][j] = first -> matrix[i][j] -> data * other -> matrix[i][j];
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
                difference -> matrix[i][j] = first -> matrix[i][j] + other -> matrix[i][j] -> data;
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}


Matrix<long double>* matrix_operators::add(const NeuralMatrix* first, const Matrix<long double>* other) {
    if(first -> N == other -> N && first -> M == other -> M) {
        Matrix<long double> *difference = new Matrix<long double>(first -> N, first -> M);
        if(difference == nullptr) {
            return nullptr;
        }
        register size_t i, j;
        for(i = 0; i < first -> N; ++i) {
            for(j = 0; j < first -> M; ++j) {
                // for operators between trivial matrices and neural matrices, the
                difference -> matrix[i][j] = first -> matrix[i][j] -> data + other -> matrix[i][j];
            }
        }
        return difference;
    } else {
        throw std::length_error("Dimension mismatch");
    }
}

Matrix<long double>* matrix_operators::create(const NeuralMatrix *other, const matrix_operators::Mode mod) {
    Matrix<long double> *new_matrix = new Matrix<long double>(other -> N, other -> M);
    if (new_matrix == nullptr) {
        std::cerr << "Error: Failed to copy NeuralMatrix object at [" << other << "]; not enough space\n";
        return nullptr;
    }
    register size_t i, j;
    switch(mod) {
        case matrix_operators::data: { // data
            for (i = 0; i < other->N; ++i) {
                for (j = 0; j < other->M; ++j) {
                    new_matrix -> matrix[i][j] = other -> matrix[i][j] -> data;
                }
            }
            return new_matrix;
        };
        case matrix_operators::function: {
            for (i = 0; i < other->N; ++i) {
                for (j = 0; j < other->M; ++j) {
                    new_matrix -> matrix[i][j] = other -> matrix[i][j] -> function;
                }
            }
            return new_matrix;
        };
        case matrix_operators::derivative: {
            for (i = 0; i < other->N; ++i) {
                for (j = 0; j < other->M; ++j) {
                    new_matrix -> matrix[i][j] = other -> matrix[i][j] -> function_derivative;
                }
            }
            return new_matrix;
        };
    }
}

Matrix<long double>* matrix_operators::create_randomized_matrix(const size_t N, const size_t M,
                                                                long double mean, long double stddev) {
    Matrix<long double> *new_matrix = new Matrix<long double>(N, M);
    std::mt19937_64 eng{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::normal_distribution<long double> distribution(mean, stddev);
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            new_matrix -> matrix[i][j] = distribution(eng);
        }
    }
    return new_matrix;
}


#pragma clang diagnostic pop