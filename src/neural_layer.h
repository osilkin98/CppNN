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

    NeuralLayer& operator=(const NeuralLayer& other);

    virtual NeuralLayer(const size_t layer_size, const size_t previous_layer_size);

    virtual NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer();

    virtual void update(const NeuralLayer& other) const;

    friend class NeuralNetwork;
};


#endif //NEURALNETWORKS_NEURALLAYER_H
