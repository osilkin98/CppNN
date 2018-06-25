//
// Created by Oleg on 6/14/2018.
//

#include "nn_utils.h"
//
// Created by oleg on 6/4/18.
//
#include <iostream>
#include <cmath>
#include <stdexcept>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"


/************ NEURON IMPLEMENTATION *************/

const long double Neuron::operator()(const long double input)  {
    data = input;
    function = activation_function(input);
    function_derivative = activation_function_prime(input);
    return function;
}


// for "firing" the neuron
const long double Neuron::operator()(void) {
    return function;
}


// for setting the values of Neuron objects from just one input
const long double Neuron::set(const Neuron::ld input) {
    data = input;
    function = activation_function(input);
    function_derivative = activation_function_prime(input);
    return function;
}

// activation function
const long double Neuron::activation_function(const long double input) const {
    return exp(input) / (exp(input) + 1);
}

// activation function
const long double Neuron::activation_function_prime(const long double input) const {
    return Neuron::activation_function(input) * (1 - Neuron::activation_function(input));
}


// print function
void Neuron::print(void) const {
    /*
    std::cout << '\n' << this << ": {\n";
    std::cout << "\tx: " << data << "\n\tσ(x): "
              << function << "\n\tσ'(x): " << function_derivative << "\n};\n";
              */
    std::cout << data << " ";
}


Neuron* Neuron::copy(void) const {
    Neuron* new_neuron = new Neuron(data);
    return new_neuron;
}


/************ NEURAL MATRIX IMPLEMENTATION *******************/


/***** CONSTRUCTORS **********/

NeuralMatrix::NeuralMatrix(const std::vector<long double> &vec) : Matrix<Neuron* >(vec.size(), 1) {
    register size_t i;
    for(i = 0; i < N; ++i) {
        matrix[i][0] = new Neuron(vec[i]);
    }
}

NeuralMatrix::NeuralMatrix(const std::vector<std::vector<long double> > &matrix_other)
        : Matrix<Neuron *>(matrix_other.size(), matrix_other[0].size()) {
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        if(matrix_other[i].size() != M) {
            throw std::invalid_argument("Matrix passed is not rectangular");
        }
        for(j = 0; j < M; ++j) {
            matrix[i][j] = new Neuron(matrix_other[i][j]);
        }
    }

}

// pointers are not initialized in the Matrix<Neuron *> call
NeuralMatrix::NeuralMatrix(const size_t n, const size_t m, bool is_null) : Matrix<Neuron *>(n, m) {
    if(!is_null) {
        // size_t sum = 0;
        register size_t i, j;
        for (i = 0; i < N; ++i) {
            for (j = 0; j < M; ++j) {

                this->matrix[i][j] = new Neuron;
                // sum += sizeof(matrix[i][j]);
            }
        }
        // std::cout << "Allocated " << sum << "B of memory at " << this << "\n";
    }
}
// deconstructor
NeuralMatrix::~NeuralMatrix() {
    register size_t i, j;
    // size_t sum = 0;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            // sum += sizeof(matrix[i][j]);
            delete matrix[i][j];
            matrix[i][j] = nullptr;
        }
    }
    // std::cout << "Freed " << sum << "B of memory at " << this << "\n";
}

NeuralMatrix *NeuralMatrix::operator*(const NeuralMatrix *other) const {
    if(Matrix<Neuron *>::M == other -> N) {
        NeuralMatrix *new_layer = new NeuralMatrix(Matrix<Neuron *>::N, other -> M);
        size_t i, j;
        register size_t k;
        for(i = 0; i < new_layer -> N; ++i) {
            for(j = 0; j < new_layer -> M; ++j) {
                for(k = 0; k < Matrix<Neuron *>::N; ++k) {
                    (new_layer -> matrix[i][j]) -> data +=
                            (this -> matrix[i][k]) -> data * (other -> matrix[k][j]) -> data;
                }
            }
        }
        return new_layer;
    } else {
        std::cerr << "Matrix Multiplication: Dimensions Mismatched\n";
        return nullptr;
    }
}

NeuralMatrix *NeuralMatrix::hadamard_product(const NeuralMatrix *other) const {
    if(equal_size(*other)) {
        NeuralMatrix *new_layer = new NeuralMatrix(N, M);
        register size_t i, j;
        std::cerr << "Computing hadamard product for the following indices: ";
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                std::cerr << "(" << i << ", " << j << ") ";
                new_layer -> at(i, j) = this -> matrix[i][j] -> data * other -> matrix[i][j] -> data;
            }
        }
        std::cerr << "\n";
        return new_layer;
    } else {
        std::cerr << "Error: Hadamard product for:"  << this << ", dimension mismatched with " << other << "\n";
        return nullptr;
    }
}

NeuralMatrix *NeuralMatrix::operator+(const NeuralMatrix *other) const {
    if(equal_size(*other)) {
        NeuralMatrix *new_layer = new NeuralMatrix(N, M);
        if(!new_layer) {
            std::cerr << "Error at " << this << ": cannot allocate new matrix, not enough space\n";
            return nullptr;
        }
        register size_t i, j;

        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                new_layer -> matrix[i][j] -> data = matrix[i][j] -> data + other -> matrix[i][j] -> data;
            }
        }
        return new_layer;
    } else {
        std::cerr << "Error adding [" << other << "] to [" << this << "]: Dimension Mismatch\n";
        return nullptr;
    }
}

NeuralMatrix *NeuralMatrix::operator-(const NeuralMatrix *other) const {
    if(equal_size(*other)) {
        NeuralMatrix *new_layer = new NeuralMatrix(N, M);
        if(!new_layer) {
            std::cerr << "Error at " << this << ": cannot allocate new matrix, not enough space\n";
            return nullptr;
        }
        register size_t i, j;

        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++j) {
                new_layer -> matrix[i][j] -> data = matrix[i][j] -> data - other -> matrix[i][j] -> data;
            }
        }
        return new_layer;
    } else {
        std::cerr << "Error subtracting [" << other << "] to [" << this << "]: Dimension Mismatch\n";
        return nullptr;
    }
}

NeuralMatrix::NeuralMatrix(const NeuralMatrix& other) : Matrix<Neuron *>(other.N, other.M) {
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            // assumes that the copy constructor for the Neuron works correctly
            matrix[i][j] = new Neuron(*other.matrix[i][j]);
        }
    }
}

NeuralMatrix* NeuralMatrix::transpose(const NeuralMatrix* other) {
    NeuralMatrix *new_mat = new NeuralMatrix(other -> M, other -> N, true);
    register size_t i, j;
    for(i = 0; i < other -> N; ++i) {
        for(j = 0; j < other -> M; ++j) {
            new_mat -> matrix[j][i] = other -> matrix[i][j] -> copy();
        }
    }
    return new_mat;
}


void NeuralMatrix::print(void) const { register size_t i, j;
    std::cout << "Printing NeuralMatrix object at " << this << ":\n";
    for(i = 0; i < N; ++i) {
        std::cout << "[ ";
        for(j = 0; j < M; ++j) {
            matrix[i][j] -> print();
            std::cout << " ";
        }
        std::cout << "]\n";
    }
    std::cout << std::endl;
}

NeuralMatrix* NeuralMatrix::transpose(void) const {
    NeuralMatrix *copy = new NeuralMatrix(M, N, true);
    if(copy == nullptr) {
        std::cerr << "Error: Memory Allocation Failed at " << this << '\n';
        return nullptr;
    }
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            copy -> matrix[j][i] = matrix[i][j] -> copy();
        }
    }
    return copy;

}

void NeuralMatrix::transpose_self() {
    std::vector< std::vector< Neuron *> > new_matrix(M, std::vector< Neuron *>(N, nullptr));
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            new_matrix[j][i] = matrix[i][j];
        }
    }
    matrix = new_matrix;

    N = matrix.size();
    M = matrix[0].size();
}

#pragma clang diagnostic pop
