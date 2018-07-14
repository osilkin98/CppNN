//
// Created by Oleg on 6/14/2018.
//
#include "namespaces.h"
#include "neural_network.h"
#include "matrix_operators.h"


using namespace neural_networks;

/************ CONSTRUCTORS AND DESTRUCTORS *******************************/
NeuralNetwork::NeuralNetwork(const size_t *dimensions, const size_t N, std::string new_label, long double rate)
        : layers(N, nullptr), label(new_label), learning_rate(rate) {
    layers[0] = new utilities::NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < N; ++i) {
        layers[i] = new utilities::NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

NeuralNetwork::NeuralNetwork(const std::vector<size_t>& dimensions, std::string new_label, long double rate) :
        layers(dimensions.size(), nullptr), label(new_label), learning_rate(rate) {
    layers[0] = new utilities::NeuralLayer(dimensions[0], 0);
    for(register size_t i = 1; i < dimensions.size(); ++i) {
        layers[i] = new utilities::NeuralLayer(dimensions[i], dimensions[i - 1]);
    }
}

/* this is a copy constructor to copy neural networks
 * must be modified in the future when various learning models are implemented */
NeuralNetwork::NeuralNetwork(const NeuralNetwork &other) : layers(other.layers.size()), learning_rate(other.learning_rate) {
    const size_t N = other.layers.size();
    for(register size_t i = 0; i < N; ++i) {
        layers[i] = new utilities::NeuralLayer(*other.layers[i]);
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
        layers[i] -> update();
    }
}

/* ACCESSOR METHODS ENABLE THE USER TO DEBUG THEIR NEURAL NETWORK BY ACCESSING SPECIFIC LAYERS */

const utilities::NeuralLayer* NeuralNetwork::operator[](const size_t index) const {
    if(index < layers.size()) {
        return layers[index];
    } else {
        std::cerr << "Error at " << this << ": Index passed in (" << index << ") is larger \
        than NeuralNetwork size (" << layers.size() << ")\n";
        return nullptr;
    }
}


utilities::NeuralLayer* NeuralNetwork::operator[](const size_t index) {
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


/* Simple Back-propogation routine, an amortized lookup table in order to avoid recursive overhead
 *
 * In the future the weight matrix and the bias vector should be placed in different containers that
 * are not all just instances of NeuralMatrix which is just an extension of Matrix<Neuron *>,
 * since the extra neuron container takes up at least 3x as much as a normal long double would,
 * it's unnecassary to use them just to store long doubles.
 *
 * For the time being it's convenient but once the basic framework for this library has been built we will
 * trim the fat and that includes eliminating the extra overhead caused by resorting to use Neurons instead of just
 * long doubles
 *
 * */
void NeuralNetwork::back_propogate(const std::vector<long double> &correct_data) const {
    // check to see if the given data set matches the size of the output vector
    if(correct_data.size() != layers[layers.size() - 1] -> data -> N) {
        throw std::length_error("Length of given dataset doesn't match up with output layer");
    }

    /* we need to amortize the error so we can quickly look it up later
    * the size that will actually be in use is layers.size() - 1 in practice but it makes it easier to access
    * I don't think there's any real reason to keep a vector of all the error vectors, since realistically
    * you're only going to be accessing the last ones, but it's nice to keep a reference of them anyway.
    * At some point the NeuralMatrix pointer will become a smart pointer and I'll be able to return these
    * without getting a bunch of cloggged up memory */
    std::vector< utilities::Matrix<long double> *> error_vectors(layers.size(), nullptr);
    // should create a copy of the last layer (output)
    // initialize last error vector to contain the values of the data vector's function
    error_vectors[error_vectors.size() - 1] =
            utilities::matrix_operators::create(layers[layers.size() - 1] -> data,
                                                utilities::matrix_operators::function);


    // data.size = length of output layer

    // loop creates the correct values for the error vector at the end
    for(register size_t i = 0; i < correct_data.size(); ++i) {
        error_vectors[error_vectors.size() - 1] -> matrix[i][0] =
                (layers[layers.size() - 1] -> data -> matrix[i][0] -> function - correct_data[i]) *
                layers[layers.size() - 1] -> data -> matrix[i][0] -> function_derivative;
    }
    utilities::Matrix<long double> *temp = NULL, *wt = NULL;
    long double del = 0;
    register size_t i = 0, j = 0, k = 0;
    // this loop performs the routine delta(l) = ((transpose(weight(l+1)) * delta(l+1)) * sigma'(z(l))
    for(i = error_vectors.size() - 2; i != 0; --i) {
        // here we have to get a copy of the transpose matrix
        wt = layers[i + 1] -> weights -> transpose();

        // this performs the matrix multiplication of weight(l+1)^T * delta(l+1)
        temp = *wt * error_vectors[i + 1];

        /* now that we have completed the matrix multiplication we'll need to actually compute the
         * element-wise product for ((w(l+1)^T) * delta(l+1)) (x) sigma'(z'(l)) */
        for(j = 0; j < temp -> N; ++j) {

            /* we'll set each individual element equal to the element wise product of the lefthand side and righthand
             * side of what should be two column vectors, we will update that value, save it, and then multiply it
             * by the learning rate, and save that as our del. This is what we'll subtract from the bias vector and
             * the weights matrix in order to back-propogate correctly
             */
            del = learning_rate * (temp -> matrix[j][0] *=
                                           layers[i] -> data -> matrix[j][0] -> function_derivative);
            // subtract the delta from the bias
            layers[i] -> bias -> matrix[j][0]-= del;
            // for the weight matrix, it's dC/d(w^(l)_{j,k}) = a^(l-1)_k * del(l)_j, so we have to multiply through
            // each value in order to update the weights matrix
            for(k = 0; k < layers[i - 1] -> data -> N; ++k) {
                layers[i] -> weights -> matrix[j][k] -= layers[i - 1] -> data -> matrix[k][0] -> data * del;
            }
        }
        temp -> print();
        /* finally, since we're done computing the hadamard product of the lefthand side and the righthand side
         * we place the temp pointer in our actual error_vectors vector and delete the transpose we used
         */
        error_vectors[i] = temp;
        delete wt;
    }
    // to make sure this works correctly
    if(error_vectors[0] != nullptr) {
        std::cerr << "Error: the 0th index of error_vector non-null\n";
    }

    for(auto& item : error_vectors) {
        delete item;
    }
}