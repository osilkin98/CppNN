//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURAL_NETWORK_H
#define NEURALNETWORKS_NEURAL_NETWORK_H

#include "neural_layer.h"
#include <vector>

class NeuralNetwork {
private:
    std::vector< NeuralLayer *> layers;

    void set_data(const std::vector<long double>& data);
public:

    virtual NeuralNetwork(const size_t *dimensions, size_t N);

    virtual NeuralNetwork(const std::vector<size_t>& dimensions);

    virtual NeuralNetwork(const NeuralNetwork& other);

    virtual ~NeuralNetwork();

    // virtual void feed_forward(void);
};

#endif //NEURALNETWORKS_NEURAL_NETWORK_H
