#include <iostream>
#include "src/linear_algebra.h"
#include "src/neural_network.h"
// #include "linear_algebra.cpp"

// #include "linear_algebra.cpp"

int main(void) {
    NeuralMatrix *one = new NeuralMatrix(4, 1), *two = new NeuralMatrix(4, 1);
    one -> print();
    two -> print();
    for(int i = 0; i < 4; ++i) {
        one -> at(i) = static_cast<long double>(i+1);
        two -> at(i) = static_cast<long double>((i + 1) * 2);
    }
    one -> print();
    two -> print();
    /*std::cout << one << " (*) " << two << std::endl;*/
    NeuralMatrix *three = two -> transpose();

    if(three != nullptr) {
        three->print();
        three->at(0, 1) = 35;
        three->print();
    }
    two -> print();
    // NeuralMatrix *four = three -> transpose();

    delete one;
    delete two;
    delete three;

    /*
    std::vector<size_t> sizes = {3, 4, 2};
    NeuralNetwork NN(sizes);
    std::vector<long double> data = {1, 2, 3};
    NN.set_data(data);
    NN.feed_forward();
    NN.print_all();
    std::vector<long double> back_data = NN.get_data_vector();
    for(size_t i = 0; i < back_data.size(); ++i) {
        std::cout << back_data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
     */
    return 0;
}