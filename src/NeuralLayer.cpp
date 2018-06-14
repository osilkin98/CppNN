//
// Created by Oleg on 6/14/2018.
//

#include "NeuralLayer.h"

template <typename T>
void pointer_assign(const T& *prev_ptr, const T& *new_ptr);

void NeuralLayer::clean(void) {
    delete data;
    data = NULL;
    delete bias;
    bias = NULL;
    delete weights;
    weights = NULL;
}

NeuralLayer::NeuralLayer(const size_t layer_size, const size_t previous_layer_size = 0) {
    if(previous_layer_size) { // if we have a specifed size for the previous layer
        data = new NeuralMatrix(layer_size, 1);
        weights = new NeuralMatrix(layer_size, previous_layer_size);
        bias = new NeuralMatrix(layer_size, 1);
    } else { // otherwise this is the first (input) layer, so we don't create weights + bias
        data = new NeuralMatrix(layer_size, 1);
        bias = NULL;
        weights = NULL;
    }
}

NeuralLayer& NeuralLayer::operator=(const NeuralLayer& other) {
    pointer_assign(bias, other.bias);
    pointer_assign(weights, other.weights);
    pointer_assign(data, other.data);
}


/* */
template <typename T>
void pointer_assign(const T& *old_ptr, const T& *new_ptr) {
    T *temp = old_ptr;
    old_ptr = new_ptr;
    delete temp;
}