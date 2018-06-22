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
public:

    NeuralNetwork(const size_t *dimensions, const size_t N);

    NeuralNetwork(const std::vector<size_t>& dimensions);

    NeuralNetwork(const NeuralNetwork& other);

    ~NeuralNetwork(void);

    // virtual void feed_forward(void);
};

#endif //NEURALNETWORKS_NEURAL_NETWORK_H
