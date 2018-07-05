//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURALLAYER_H
#define NEURALNETWORKS_NEURALLAYER_H

#include "neural_matrix.h"
#include "namespaces.h"

class neural_networks::utilities::NeuralLayer {
private:
    void clean();

    NeuralMatrix *data;

    neural_networks::utilities::components::Matrix<long double> *bias, *weights;

    size_t N;

public:

    // operator to assign one neural layer object to another
    NeuralLayer& operator=(const NeuralLayer& other);



    explicit NeuralLayer(size_t layer_size, size_t previous_layer_size = 0);

    NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer();

    void print() const;
    virtual void update(const NeuralLayer& other) const;

    friend class neural_networks::NeuralNetwork;
};


#endif //NEURALNETWORKS_NEURALLAYER_H
