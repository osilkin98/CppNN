//
// Created by oleg on 6/4/18.
//

#include "linear_algebra.h"

#ifndef NEURALNETWORK_UTILS_H
#define NEURALNETWORK_UTILS_H


/***** ACTIVATION FUNCTIONS ********/

long double sigmoid(const long double input);

long double sigmoid_derivative(const long double input);

long double ReLU(const long double input);

long double ReLU_derivative(const long double input);


// template <typename T>
struct Neuron {
    typedef long double ld;
    long double data, function, function_derivative;

    // returns the activation of the function
    const ld operator()(void);

    const ld operator()(const ld input);

    const ld activation_function(const ld input) const;

    const ld activation_function_prime(const ld input) const;

    void print(void) const;

    Neuron(void) : data(0), function(0.5), function_derivative(0.25) {}

    Neuron(const long double input) : data(input),
                                      function(activation_function(input)),
                                      function_derivative(activation_function_prime(input))
    { }

    Neuron(const Neuron& other) : data(other.data),
                                  function(other.function),
                                  function_derivative(other.function_derivative) { }
};


class NeuralLayer : public Matrix<Neuron *> {
public:


    NeuralLayer *operator*(const NeuralLayer *other) const;

    NeuralLayer *hadamard_product(const NeuralLayer *other) const;

    NeuralLayer *operator+(const NeuralLayer *other) const;

    NeuralLayer *operator-(const NeuralLayer *other) const;

    NeuralLayer(const NeuralLayer& other);

    NeuralLayer(const size_t n, const size_t m = 1) : Matrix<Neuron*>(n, m) { }

    void print(void) const;


};



#endif //NEURALNETWORKS_NN_UTILS_H
