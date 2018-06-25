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

    long double learning_rate;

public:


    // for labeling neural networks
    std::string label;

    /* In the future the set_data routine should be templated to accept *ANY* type of container */
    virtual void set_data(const std::vector<long double>& data) const;

    virtual void set_data(const long double *data, size_t N) const;

    // forward-propogation routine, this is written to be very abstracted
    virtual void feed_forward() const;

    virtual void back_propogate(const std::vector<long double>& correct_data) const;
    /* labels for constructors are optional */

    NeuralNetwork(const size_t *dimensions, size_t N, std::string new_label, long double rate = 0.015);

    explicit NeuralNetwork(const std::vector<size_t>& dimensions,
                           std::string new_label = std::string(), long double rate = 0.015);

    NeuralNetwork(const NeuralNetwork& other);

    virtual ~NeuralNetwork();

    // to get a copy of the final data
    virtual std::vector<long double> get_data_vector() const;

    // to be able to index a certain layer of the network
    virtual const NeuralLayer* operator[](size_t index) const;

    virtual NeuralLayer *operator[](size_t index);



    void print_all() const;

};

#endif //NEURALNETWORKS_NEURAL_NETWORK_H
