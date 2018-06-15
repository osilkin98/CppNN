//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURAL_NETWORK_H
#define NEURALNETWORKS_NEURAL_NETWORK_H

#include "NeuralLayer.h"
#include <vector>

class NeuralNetwork {
private:
    std::vector< NeuralLayer *> layers;
public:

    NeuralNetwork(const int *dimensions, const size_t N);

    NeuralNetwork(const std::vector<int> dimensions);

    NeuralNetwork(const NeuralNetwork& other);

    ~NeuralNetwork(void);


};

#endif //NEURALNETWORKS_NEURAL_NETWORK_H
