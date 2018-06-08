//
// Created by oleg on 6/4/18.
//

#include "nn_utils.h"
#include <iostream>
#include <cmath>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"


/************ NEURON IMPLEMENTATION *************/

const long double Neuron::operator()(const long double input)  {
    data = input;
    function = activation_function(input);
    function_derivative = activation_function_prime(input);
    return function;
}

const long double Neuron::operator()(void) {
    return function;
}

const long double Neuron::activation_function(const long double input) const {
    return exp(input) / (exp(input) + 1);
}

const long double Neuron::activation_function_prime(const long double input) const {
    return Neuron::activation_function(input) * (1 - Neuron::activation_function(input));
}

void Neuron::print(void) const {
    std::cout << '\n' << this << ": {\n";
    std::cout << "\tx: " << data << "\n\tσ(x): "
              << function << "\n\tσ'(x): " << function_derivative << "\n};\n";
}

/************ NEURAL NETWORK IMPLEMENTATION *******************/

NeuralLayer::NeuralLayer(const size_t n, const size_t m = 1) : Matrix<Neuron *>(n, m) {
    register size_t i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            this -> matrix[i][j] = new Neuron;
        }
    }
}

NeuralLayer* NeuralLayer::operator*(const NeuralLayer *other) const {
    if(Matrix<Neuron *>::M == other -> N) {
        NeuralLayer *new_layer = new NeuralLayer(Matrix<Neuron *>::N, other -> M);
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
        return NULL;
    }
}

NeuralLayer* NeuralLayer::hadamard_product(const NeuralLayer *other) const {
    if(equal_size(other)) {
        NeuralLayer *new_layer = new NeuralLayer(N, M);
        register size_t i, j;
        for(i = 0; i < N; ++i) {
            for(j = 0; j < M; ++i) {
                new_layer -> matrix[i][j] -> data = this -> matrix[i][j] -> data * other -> matrix[i][j] -> data;
            }
        }
        return new_layer;
    } else {
        std::cerr << "Error: Hadamard product for:"  << this << ", dimension mismatched with " << other << "\n";
        return NULL;
    }
}




#pragma clang diagnostic pop
