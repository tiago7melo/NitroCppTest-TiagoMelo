#!/bin/bash

# This only works for Linux, need a streamlined portable script
# Good for now, just for testing in my Linux environment

#rm -rf build
rm -rf rectangle_intersect
mkdir build
cmake -S . -B build -DENABLE_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build 
cmake --install build