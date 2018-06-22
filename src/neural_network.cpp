//
// Created by Oleg on 6/14/2018.
//

#include "neural_network.h"

/************ CONSTRUCTORS AND DESTRUCTORS *******************************/
NeuralNetwork::NeuralNetwork(const size_t *dimensions, const size_t N) : layers(N, nullptr) {
    layers[0] = new NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < N; ++i) {
        layers[i] = new NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

NeuralNetwork::NeuralNetwork(const std::vector<size_t>& dimensions) :
        layers(dimensions.size(), nullptr) {
    layers[0] = new NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < dimensions.size(); ++i) {
        layers[i] = new NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

/* this is a copy constructor to copy neural networks
 * must be modified in the future when various learning models are implemented */
NeuralNetwork::NeuralNetwork(const NeuralNetwork &other) : layers(other.layers.size()) {
    const size_t N = other.layers.size();
    for(register size_t i = 0; i < N; ++i) {
        layers[i] = new NeuralLayer(*other.layers[i]);
    }
}

NeuralNetwork::~NeuralNetwork() {
    for(auto& v : layers) {
        delete v;
    }
}

/********************** FUNCTIONS ******************************/

void NeuralNetwork::set_data(const std::vector<long double> &data) const {
    if(data.size() != (*layers[0]).N ) { // our data vector is a different size than input layer
        std::cerr << "Error in NeuralNetwork object at " << this << '\n';
        throw "Input Data Length Mismatch";
    } else {
        const size_t N = data.size();
        for(register size_t i = 0; i < N; ++i) {
            layers[0] -> data -> matrix[i][0] -> data = data[i];
        }
    }
}

void NeuralNetwork::feed_forward(void) const {
    for(register size_t i = 1; i < layers.size(); ++i) {
        layers[i] -> update(*layers[i - 1]);
    }
}

