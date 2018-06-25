//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURALLAYER_H
#define NEURALNETWORKS_NEURALLAYER_H

#include "nn_utils.h"

class NeuralLayer {
private:
    void clean();

    NeuralMatrix *data, *bias, *weights;

public:
    const size_t N;

    // operator to assign one neural layer object to another
    NeuralLayer& operator=(const NeuralLayer& other);



    NeuralLayer(size_t layer_size, size_t previous_layer_size);

    NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer();

    void print() const;
    virtual void update(const NeuralLayer& other) const;

    friend class NeuralNetwork;
};


#endif //NEURALNETWORKS_NEURALLAYER_H
