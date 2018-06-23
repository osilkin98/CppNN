//
// Created by Oleg on 6/14/2018.
//

#include "neural_layer.h"


void NeuralLayer::clean(void) {
    delete data;
    data = nullptr;
    delete bias;
    bias = nullptr;
    delete weights;
    weights = nullptr;
}

NeuralLayer::NeuralLayer(const size_t layer_size, const size_t previous_layer_size = 0) : N(layer_size) {
    data = new NeuralMatrix(layer_size, 1);
    if(previous_layer_size) { // if we have a specifed size for the previous layer
        weights = new NeuralMatrix(layer_size, previous_layer_size);
        bias = new NeuralMatrix(layer_size, 1);
    } else { // otherwise this is the first (input) layer, so we don't create weights + bias
        bias = nullptr;
        weights = nullptr;
    }
}

NeuralLayer::NeuralLayer(const NeuralLayer &other) : N(other.N) {
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
    NeuralMatrix *temp = weights;
    weights = other.weights;
    delete temp;
    temp = bias;
    bias = other.bias;
    delete temp;
    temp = data;
    data = other.data;
    delete temp;
    temp = nullptr;

}

void NeuralLayer::update(const NeuralLayer &other) const {
    if(bias -> M != other.data -> N) {
        std::cerr << "During update operation, bias M [" << bias -> M << "] at " << bias
        << " in object " << this << " does not match input vector size N [" << other.data -> N
        << "] at " << other.data << '\n';
    }
    register size_t i;
    long double sum;
    if(other.bias) { // if we're not dealing with the input layer
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = 0 + bias -> matrix[elem][0] -> data;
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i] -> data *
                                         other.data -> matrix[i][0] -> function;
            }
            data -> matrix[elem][0] -> set(sum);
        }
    } else {
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = 0 + bias -> matrix[elem][0] -> data;
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i] -> data *
                       other.data -> matrix[i][0] -> data;
            }
            data -> matrix[elem][0] -> set(sum);
        }
    }
}

