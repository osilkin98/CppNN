//
// Created by oleg on 6/4/18.
//

#ifndef NEURALNETWORK_UTILS_H
#define NEURALNETWORK_UTILS_H

#include "matrix.h"
#include "namespaces.h"




// template <typename T>
struct neural_networks::utilities::Neuron {
    typedef long double ld;
    long double data, function, function_derivative;

    // returns the activation of the function
    virtual const ld operator()();

    virtual const ld operator()(ld input);

    virtual const ld set(ld input);

    virtual const ld activation_function(ld input) const;

    virtual const ld activation_function_prime(ld input) const;

    virtual void print() const;

    virtual Neuron* copy() const;

    Neuron() : data(0), function(0.5), function_derivative(0.25) {}

    explicit Neuron(const long double input) : data(input),
                                               function(activation_function(input)),
                                               function_derivative(activation_function_prime(input))
    { }

    Neuron(const Neuron& other) = default;
};


class neural_networks::utilities::NeuralMatrix
        : public neural_networks::utilities::Matrix<Neuron *> {
public:


    NeuralMatrix *operator*(const NeuralMatrix *other) const;

    NeuralMatrix *hadamard_product(const NeuralMatrix *other) const;

    NeuralMatrix *operator+(const NeuralMatrix *other) const;

    NeuralMatrix *operator-(const NeuralMatrix *other) const;



    // copy constructor
    NeuralMatrix(const NeuralMatrix& other);

    /* constructors for 1-dimensional & 2-dimensional STL vectors*/
    explicit NeuralMatrix(const std::vector< long double>& vec);

    // 2-dimensiona std::vector
    explicit NeuralMatrix(const std::vector< std::vector<long double> >& matrix);

    // standard constructor
    explicit NeuralMatrix(size_t n, size_t m = 1, bool nullified = false, bool random = false);

    // @override
    ~NeuralMatrix() override;

    static NeuralMatrix* transpose(const NeuralMatrix* other);

    NeuralMatrix* transpose() const override;

    void transpose_self();


    void print() const override;

    long double& at(const size_t i, const size_t j = 0) {
        if(i < N && j < M) {
            return matrix[i][j] -> data;
        } else {
            std::cerr << "Dimension mismatch, (" << i << ", " << j << ") is out of bounds.\n";
        }
    }

};



#endif //NEURALNETWORKS_NN_UTILS_H
