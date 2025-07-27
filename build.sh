#!/bin/bash

# TODO: This only works for Linux, need a streamlined portable script
# Good for now, just for testing in my Linux environment
# TODO: also needs portable exec permissions

rm -rf build
rm -rf rectangle_intersect
mkdir build
cmake -S . -B build -DENABLE_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cmake --install build