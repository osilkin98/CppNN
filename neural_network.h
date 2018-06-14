//
// Created by Oleg on 6/11/2018.
//

#ifndef NEURALNETWORKS_NEURAL_NETWORK_H
#define NEURALNETWORKS_NEURAL_NETWORK_H

#include "nn_utils.h"

class NeuralLayer {
public:
    NeuralMatrix *data, *bias, *weights;

    NeuralLayer(const size_t layer_size, const size_t previous_layer_size);

    NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer(void);
};

class NeuralNetwork {
private:
    std::vector<NeuralMatrix *> network;


public:

    explicit NeuralNetwork(const size_t N = 0) : network(N, NULL) { }

    // for explicitly defining an array of N layers and each layer's dimensions
    NeuralNetwork(const int *layer_dimensions, const size_t N);

    NeuralNetwork(const std::vector<int>& layer_dimensions);

    NeuralNetwork(const NeuralNetwork& other);

    void set_dimension(const size_t index, const int rows, const int cols);

    ~NeuralNetwork(void);
};


#endif //NEURALNETWORKS_NEURAL_NETWORK_H
