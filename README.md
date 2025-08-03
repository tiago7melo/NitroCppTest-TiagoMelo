# NitroCppTest-TiagoMelo
CLI app that will intersect axis aligned rectangles given a JSON file that describes a canvas of potentially intersecting rectangles.

Implemented as part of C++ proficiency assessment for Nitro. You can find the full specification for this assessment as a PDF file under the root folder of this repository: [**Nitro C++ Proficiency Test Specification**](https://github.com/tiago7melo/NitroCppTest-TiagoMelo/blob/main/C___Proficiency_test_-_Updated.pdf)

## Dependencies
This section details dependencies for the project to build successfully.
### Environment
You will require the following to be installed in your environment to build the project:
* C++ compiler with C++23 standard support: https://en.cppreference.com/w/cpp/compiler_support/23
* CMake (v3.15+): https://cmake.org/cmake/help/book/mastering-cmake/chapter/Getting%20Started.html
* Git SCM (for pulling the project): https://git-scm.com/downloads
### Third party libraries
Building the project will also automatically fetch the following third party libraries:
* nhlohmann::json  (Release 3.12.0): https://github.com/nlohmann/json/releases/tag/v3.12.0
* GoogleTest (Release 1.17.0): https://github.com/google/googletest/releases/tag/v1.17.0
## Getting the Project
To get the project, it is recommended that you simply

## Building
This section describes two ways of building the project:
* Complete build that includes the test suite: [Build with Tests](#build-with-tests)
* Compact build that only includes the main executable: [Build with no Tests](#build-with-no-tests)
### Build with Tests
From the root directory of the repository, run following commands:
```bash
    mkdir build
    cmake -S . -B build -DENABLE_TESTS=ON
    cmake --build build --config RelWithDebInfo
    cmake --install build
```
#TODO: de
### Build with no Tests
From the root directory of the repository, run the following commands:
```bash

```

### Clean Install
In case of error during installing, the current installation can be removed by removing the "build" folder under the root directory of the project.

A clean installation can then be performed using the commands from the subsections above.

## Usage

The format of your JSON file should be: 
-> Contains ["rects"]
-> Each rects has x,y,z,w




Running the tests:


# TODO: specify that the build commands need to be ran from the root dir of the project

# TODO: specify how to give the option to exceed the default limit of 10 rectangles


# include USAGE and mention that [max_rectangles] is optional

# TODO: delete build.sh and clean.sh