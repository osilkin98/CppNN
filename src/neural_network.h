//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURAL_NETWORK_H
#define NEURALNETWORKS_NEURAL_NETWORK_H

#include "neural_layer.h"
#include <vector>

class NeuralNetwork {
private:
    std::vector< NeuralLayer *> layers;
    /* In the future the set_data routine should be templated to accept *ANY* type of container */
    virtual void set_data(const std::vector<long double>& data) const;

    virtual void set_data(const long double *data, const size_t N) const;

    // forward-propogation routine, this is written to be very abstracted
    virtual void feed_forward(void) const;


public:

    virtual NeuralNetwork(const size_t *dimensions, size_t N);

    virtual NeuralNetwork(const std::vector<size_t>& dimensions);

    virtual NeuralNetwork(const NeuralNetwork& other);

    virtual ~NeuralNetwork();

    std::vector<long double>& get_data_vector(void) const;

};

#endif //NEURALNETWORKS_NEURAL_NETWORK_H
