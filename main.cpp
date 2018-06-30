#include <iostream>
#include "src/neural_network.h"
#include "src/matrix_operators.h"
// #include "linear_algebra.cpp"

// #include "linear_algebra.cpp"

int main(void) {

    Matrix<long double> *one = new Matrix<long double>(3, 4), *three, *four, *five, *six;
    NeuralMatrix *two = new NeuralMatrix(3, 4, false, true);

    std::cout << "\nOne:\n";
    one -> print();
    std::cout << "\nTwo:\n";
    two -> print();

    three = matrix_operators::add(one, two);
    four = matrix_operators::subtract(one, two);
    five = matrix_operators::hadamard_product(one, two);
    if(three != nullptr) {
        std::cout << "\nAddition:\n";
        three -> print();
        std::cout << "\nSubtraction:\n";
        four -> print();
        std::cout << "\nHadamard Product:\n";
        five -> print();
    }

    std::cout << std::endl;

    delete one;
    delete two;
    delete three;
    delete four;
    delete five;





    /*

    std::vector<size_t> sizes = {3, 4, 2};

    NeuralNetwork NN(sizes);
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
*/
    return 0;


    //return 0;
}