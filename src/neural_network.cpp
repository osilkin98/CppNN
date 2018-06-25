//
// Created by Oleg on 6/14/2018.
//

#include "neural_network.h"

/************ CONSTRUCTORS AND DESTRUCTORS *******************************/
NeuralNetwork::NeuralNetwork(const size_t *dimensions, const size_t N, std::string new_label, long double rate)
        : layers(N, nullptr), label(new_label), learning_rate(rate) {
    layers[0] = new NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < N; ++i) {
        layers[i] = new NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

NeuralNetwork::NeuralNetwork(const std::vector<size_t>& dimensions, std::string new_label, long double rate) :
        layers(dimensions.size(), nullptr), label(new_label), learning_rate(rate) {
    layers[0] = new NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < dimensions.size(); ++i) {
        layers[i] = new NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

/* this is a copy constructor to copy neural networks
 * must be modified in the future when various learning models are implemented */
NeuralNetwork::NeuralNetwork(const NeuralNetwork &other) : layers(other.layers.size()), learning_rate(other.learning_rate) {
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

/*************************************** FUNCTIONS *************************************/

// sets data using vector container
void NeuralNetwork::set_data(const std::vector<long double> &data) const {
    if(data.size() != (*layers[0]).N ) { // our data vector is a different size than input layer
        std::cerr << "Error in NeuralNetwork object at " << this << '\n';
        throw std::length_error("Length doesn't match up the size of the input data vector");
    } else {
        const size_t N = data.size();
        for(register size_t i = 0; i < N; ++i) {
            layers[0] -> data -> matrix[i][0] -> data = data[i];
        }
    }
}

// sets data using traditional C-styled array containers
void NeuralNetwork::set_data(const long double *data, const size_t N) const {
    if(N != (*layers[0]).N) {
        std::cerr << "Error in NeuralNetwork object at " << this << '\n';
        throw std::length_error("Length doesn't match up the size of the input data vector");
    } else {
        for(register size_t i = 0; i < N; ++i) {
            layers[0] -> data -> matrix[i][0] -> data = data[i];
        }
    }
}

// creates a copy of the Neural Network's produced data
std::vector<long double> NeuralNetwork::get_data_vector() const {
    size_t access = layers.size() - 1;
    size_t N = layers[access] -> N;
    std::vector<long double> data(N);
    for(register size_t i = 0; i < N; ++i) {
        data[i] = layers[access] -> data -> matrix[i][0] -> function;
    }
    return data;
}


void NeuralNetwork::feed_forward(void) const {
    for(register size_t i = 1; i < layers.size(); ++i) {
        layers[i] -> update(*layers[i - 1]);
    }
}

/* ACCESSOR METHODS ENABLE THE USER TO DEBUG THEIR NEURAL NETWORK BY ACCESSING SPECIFIC LAYERS */

const NeuralLayer* NeuralNetwork::operator[](const size_t index) const {
    if(index < layers.size()) {
        return layers[index];
    } else {
        std::cerr << "Error at " << this << ": Index passed in (" << index << ") is larger \
        than NeuralNetwork size (" << layers.size() << ")\n";
        return nullptr;
    }
}


NeuralLayer* NeuralNetwork::operator[](const size_t index) {
    if(index < layers.size()) {
        return layers[index];
    } else {
        std::cerr << "Error at " << this << ": Index passed in (" << index << ") is larger \
        than NeuralNetwork size (" << layers.size() << ")\n";
        return nullptr;
    }
}

/* PRINT FUNCTION FOR DEBUGGING */
void NeuralNetwork::print_all(void) const {
    for(size_t i = 0; i < layers.size(); ++i) {
        std::cout << "--------------------------------: LAYER " << i
                  << (!layers[i] -> weights ? " [INPUT LAYER]" : "" )
                  << " :----------------------------------------\n";

        layers[i] -> print();
    }
}


/* Simple Back-propogation routine, an amortized lookup table in order to avoid recursive overhead */
void NeuralNetwork::back_propogate(const std::vector<long double> &correct_data) const {
    // check to see if the given data set matches the size of the output vector
    if(correct_data.size() != layers[layers.size() - 1] -> data -> N) {
        throw std::length_error("Length of given dataset doesn't match up with output layer");
    }

    // we need to amortize the error so we can quickly look it up later
    // the size that will actually be in use is layers.size() - 1 in practice but it makes it easier to access
    std::vector<NeuralMatrix*> error_vectors(layers.size(), nullptr);
    // should create a copy of the last layer (output)
    error_vectors[error_vectors.size() - 1] = new NeuralMatrix(*layers[layers.size() - 1] -> data);
    // data.size = length of output layer
    for(register size_t i = 0; correct_data.size(); ++i) {

        error_vectors[error_vectors.size() - 1] -> matrix[i][0] -> set(
                (layers[layers.size() - 1] -> data -> matrix[i][0] -> function - correct_data[i]) *
                layers[layers.size() - 1] -> data -> matrix[i][0] -> function_derivative);
    }
    NeuralMatrix *temp, *wt;
    long double del;
    register size_t i, j, k;
    for(i = error_vectors.size() - 2; i != 0; --i) {
        wt = layers[i + 1] -> weights -> transpose();
        temp = *wt * error_vectors[i + 1];
        for(j = 0; j < temp -> N; ++j) {
            del = (temp -> matrix[j][0] -> data *= layers[i] -> data -> matrix[j][0] -> function_derivative);
            layers[i] -> bias -> matrix[j][0] -> data -= del;
            for(k = 0; k < layers[i - 1] -> data -> N; ++k) {
                layers[i] -> weights -> matrix[j][k] -> data -= layers[i - 1] -> data -> matrix[k][0] -> data * del;
            }
        }
    }


}