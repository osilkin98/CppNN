#include <iostream>
#include "src/linear_algebra.h"
#include "src/neural_network.h"
// #include "linear_algebra.cpp"

// #include "linear_algebra.cpp"

int main(void) {
    std::vector<size_t> sizes = {3, 4, 2};
    NeuralNetwork NN(sizes);


/*
    srand(time(0));
    std::vector<Neuron *> neurons(5, NULL);
    for(int i = 0; i < 5; ++i) {
        neurons[i] = new Neuron(-2 + ((double)rand()/RAND_MAX) * (4));
        neurons[i] -> print();
    }
    for(int i = 0; i < 5; ++i) {
        delete neurons[i];
        neurons[i] = NULL;
    }
*/

}