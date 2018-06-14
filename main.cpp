#include <iostream>
#include "src/linear_algebra.h"
// #include "linear_algebra.cpp"

// #include "linear_algebra.cpp"

int main(void) {
    Matrix<int> *my_mat = new Matrix<int>(3, 4);
    for(size_t i = 0; i < 3; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            my_mat -> matrix[i][j] = j*i + j;
        }
    }
    std::cout << "Original:\n";
    my_mat -> print();
    std::cout << "Transposed:\n";
    my_mat -> transpose();
    my_mat -> print();
    delete my_mat;
    return 0;


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