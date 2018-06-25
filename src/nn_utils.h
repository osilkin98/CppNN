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
    virtual const ld operator()(void);

    virtual const ld operator()(const ld input);

    virtual const ld set(const ld input);

    virtual const ld activation_function(const ld input) const;

    virtual const ld activation_function_prime(const ld input) const;

    virtual void print(void) const;

    virtual Neuron* copy(void) const;

    Neuron(void) : data(0), function(0.5), function_derivative(0.25) {}

    Neuron(const long double input) : data(input),
                                      function(activation_function(input)),
                                      function_derivative(activation_function_prime(input))
    { }

    Neuron(const Neuron& other) : data(other.data),
                                  function(other.function),
                                  function_derivative(other.function_derivative) { }
};


class NeuralMatrix : public Matrix<Neuron *> {
public:


    NeuralMatrix *operator*(const NeuralMatrix *other) const;

    NeuralMatrix *hadamard_product(const NeuralMatrix *other) const;

    NeuralMatrix *operator+(const NeuralMatrix *other) const;

    NeuralMatrix *operator-(const NeuralMatrix *other) const;

    NeuralMatrix(const NeuralMatrix& other);

    explicit NeuralMatrix(const size_t n, const size_t m = 1, bool nullified = false);

    // @override
    ~NeuralMatrix(void) override;

    static NeuralMatrix* transpose(const NeuralMatrix* other);

    NeuralMatrix* transpose(void) const;

    void transpose_self(void);


    void print(void) const;

    long double& at(const size_t i, const size_t j = 0) {
        if(i < N && j < M) {
            return matrix[i][j] -> data;
        } else {
            std::cerr << "Dimension mismatch, (" << i << ", " << j << ") is out of bounds.\n";
        }
    }

};



#endif //NEURALNETWORKS_NN_UTILS_H
