//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURALLAYER_H
#define NEURALNETWORKS_NEURALLAYER_H

#include "neural_matrix.h"
#include "namespaces.h"

class neural_networks::utilities::NeuralLayer {
protected:

    // method is intended for internal use in order to empty the space used instead
    // of just deleting the entire neurrallayer object in some fringe case
    void clean();

    NeuralMatrix *data;

    neural_networks::utilities::Matrix<long double> *bias, *weights;

    // label for the particular layer
    std::string label;

    // the size of the data vector
    size_t N;

    // the neurallayer from which this layer will receive its input
    const NeuralLayer *input;

public:

    // operator to assign one neural layer object to another
    NeuralLayer& operator=(const NeuralLayer& other);

    // constructor to specify an input from another layer
    explicit NeuralLayer(
            const NeuralLayer *input,
            const size_t layer_size,
            std::string label = std::string());

    // constructor to create the layer using a size specification
    // this constructor should actually NOT be used because using pointers from one NeuralLayer to another
    // is the preferred method of operation, this should be used for creating the first layer
     explicit NeuralLayer(size_t layer_size, size_t previous_layer_size = 0, std::string label = std::string());

    // copy constructor
    NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer();

    void print() const;
    virtual void update(const NeuralLayer& other) const;

    friend class neural_networks::NeuralNetwork;
};


#endif //NEURALNETWORKS_NEURALLAYER_H
