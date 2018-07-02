# Neural Networks
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE) 
[![Version](https://img.shields.io/badge/Version-0.1-brightgreen.svg)](README.md)
## Extensible Neural Network library written entirely in C++ 

### Project Goals:
This project aims to create a library for deep learning and machine 
learning with the extensibility of Google's TensorFlow, but with the 
speed and efficiency of C++. 

### Todo:
- [x] Implement Back-Propagation
- [ ] Implement Namespaces for Library Hierarchy
- [ ] Optimize Code
- [x] Move Weight & Bias from NeuralMatrix to simpler struct/class
- [ ] Parallelize Routines in order to drastically decrease runtime
- [ ] Add Functionality for Generic Evalutionary Algorithms
- [ ] Learning Model Selection
- [ ] Add Support for Convolutionary Neural Networks
- [ ] Add Support for Recurrent Neural Networks


### Where is this library right now?
This library provides basic Neural Network functionalities, such as
the ability to feed data into the network, receive an output, feed in
the "correct" data, and have it back-propogate in order to adjust its
learning mechanism. 

Unfortunately, this library is in a very early stage, so at the moment
there is nothing along the lines of multithreading or any form of parallel
computing. 

### Where does this library aim to be?
My personal goal for this library is for it to be used for anything from
a small deep learning project running on an old Thinkpad from 2005, to
large projects requiring large distributed databases to train their models.

### What needs to be added?
This code is far from optimized, and so there is a need for the least space
consumption with some of these classes that are being used. 
The weight and bias vectors in each layer are currently implemented with the
NeuralMatrix class, which requires that each element is an instance of the 
Neuron object, however all that is needed is for them to store a long double. 
Additionally, most of this code can be parallized, and so I plan on adding
CUDA routines to run on the user's GPU instead of the CPU. For those who
don't have an NVIDIA GPU, I need to add CPU multithreading. 
In the future I plan on adding compatibility for TensorCores as well, however
that is not a priority at the moment. 
