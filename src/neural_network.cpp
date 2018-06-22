//
// Created by Oleg on 6/14/2018.
//

#include "neural_network.h"

NeuralNetwork::NeuralNetwork(const size_t *dimensions, const size_t N) : layers(N, nullptr) {
    layers[0] = new NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < N; ++i) {
        layers[i] = new NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

NeuralNetwork::NeuralNetwork(const std::vector<size_t>& dimensions) :
        layers(dimensions.size(), nullptr) {
    layers[0] = new NeuralLayer(dimensions[0], 0);


}