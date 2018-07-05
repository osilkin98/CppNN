#include <iostream>
#include <random>
#include <chrono>
#include "src/neural_network.h"
#include "src/matrix_operators.h"
#include "src/namespaces.h"
// #include "linear_algebra.cpp"

// #include "linear_algebra.cpp"

template <typename T>
void print_matrix(std::vector< std::vector< T > >& mat) {
    size_t i, j;
    for(i = 0; i < mat.size(); ++i) {
        std::cout << "[ ";
        for(j = 0; j < mat[i].size(); ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "]\n";
    }
}


int main(void) {

    /*
    Matrix<long double> *one = matrix_operators::create_randomized_matrix(3, 4),
            *two = matrix_operators::create_randomized_matrix(4, 3);

    one -> print();
    two -> print();

    *one = *two;
    one -> print();
    two -> print();

    delete one;
    delete two; */




    std::vector<size_t> sizes = {3, 4, 2};
    neural_networks::NeuralNetwork NN(sizes);
    std::vector<long double> data = {1, 2, 3};
    NN.set_data(data);
    NN.feed_forward();
    NN.print_all();
    std::cout << "grabbing data\n";
    std::vector<long double> back_data = NN.get_data_vector();
    for(size_t i = 0; i < back_data.size(); ++i) {
        std::cout << back_data[i] << " ";
    }
    std::vector<long double> correct_data = {1, 0};
    std::cout << "Trying to back propogate with data correction {1, 0}\n";
    NN.back_propogate(correct_data);
    NN.print_all();
    std::cout << std::endl;

    return 0;


    //return 0;
}