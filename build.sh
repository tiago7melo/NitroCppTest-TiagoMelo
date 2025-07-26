#!/bin/bash

# TODO: This only works for Linux, need a streamlined portable script
# Good for now, just for testing my Linux environment
# TODO: also needs portable exec permissions

rm -rf build
rm -rf bin
rm -rf rectangle_intersect #TODO: make this generic naming I can change in one centralized place
mkdir build && cd build
cmake ..
cmake --build .
cp rectangle_intersect ..
cd ..