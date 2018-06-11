//
// Created by Oleg on 6/11/2018.
//

#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const int *layer_dimensions, const size_t N) {
    for(register size_t i = 0; i < N; ++i) {
        network[i] = new NeuralLayer(layer_dimensions[i], 1);
    }
}

NeuralNetwork::NeuralNetwork(const std::vector<int> &layer_dimensions) {
    for(register size_t i = 0; i < layer_dimensions.size(); ++i) {
        network[i] = new NeuralLayer(layer_dimensions[i], 1);
    }
}

// copy constructor, it should copy the network, not copy the pointer addresses
NeuralNetwork::NeuralNetwork(const NeuralNetwork &other) : network(other.network.size()){
    for(register size_t i = 0; i < network.size(); ++i) {
        network[i] = new NeuralLayer(*other.network[i]);
    }
}