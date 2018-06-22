//
// Created by Oleg on 6/14/2018.
//

#include "neural_layer.h"

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
    data = new NeuralMatrix(layer_size, 1);
    if(previous_layer_size) { // if we have a specifed size for the previous layer
        weights = new NeuralMatrix(layer_size, previous_layer_size);
        bias = new NeuralMatrix(layer_size, 1);
    } else { // otherwise this is the first (input) layer, so we don't create weights + bias
        bias = NULL;
        weights = NULL;
    }
}

NeuralLayer::NeuralLayer(const NeuralLayer &other) {
    // N should be the same for each matrix
    data = new NeuralMatrix(other.data -> N, 1);
    // this is only in the case of the input matrix, which has no weight or bias matrix
    if(!other.weights) {
        return;
    }
    bias = new NeuralMatrix(other.bias -> N, 1); // for all the matrices
    weights = new NeuralMatrix(other.weights -> N, other.weights -> M);

    size_t N = other.data -> N, M = other.weights -> M;
    register size_t i, j;

    for(i = 0; i < N; ++i) {
        data -> matrix[i][0] = other.data -> matrix[i][0];
        bias -> matrix[i][0] = other.bias -> matrix[i][0];
        for(j = 0; j < M; ++j) {
            weights -> matrix[i][j] = other.weights -> matrix[i][j];
        }
    }
}

NeuralLayer::~NeuralLayer(void) {
    delete weights;
    delete bias;
    delete data;
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