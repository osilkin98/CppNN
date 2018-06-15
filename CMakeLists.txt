cmake_minimum_required(VERSION 3.10)
project(NeuralNetworks)

set(CMAKE_CXX_STANDARD 11)
# set(SOURCE_FILES main.cpp linear_algebra.cpp)
# add_library(Linear_Algebra STATIC inear_algebra.cpp linear_algebra.h)
set(SOURCE_FILES "main.cpp" "linear_algebra.h")
#set(CMAKE_VERBOSE_MAKEFILE ON)

# add_library(linear_algebra INTERFACE)
add_executable(NeuralNetworks main.cpp src/NeuralLayer.cpp src/NeuralLayer.h src/nn_utils.cpp src/nn_utils.h src/linear_algebra.h src/neural_network.cpp src/neural_network.h)