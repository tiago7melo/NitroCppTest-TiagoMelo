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
To get the project, it is recommended that you simply clone it through Git SCM.
Here's an example how to do it through SSH:
```bash
git clone git@github.com:tiago7melo/NitroCppTest-TiagoMelo.git
```

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
This should install the main executable under the root directory of the repository.
### Build with no Tests
From the root directory of the repository, run the following commands:
```bash
mkdir build
cmake -S . -B build
cmake --build build --config Release
cmake --install build
```
This should install the main executable under the root directory of the repository.
### Clean Install
In case of error during installing, the current installation can be removed by removing the "build" folder under the root directory of the project.

A clean installation can then be performed using the commands from the subsections above.

## Usage

The main executable ```rectangle_intersect```  can take up to two arguments:
```bash
./rectangle_intersect <path/to/file.json> [max_rectangles]
```

The **first argument** should always be the path to a JSON file that abides by the following format:
* Contains an JSON object that is an array of JSON Object literals. This array but be named ```"rects"```
* Each element of the array must contain the following:
    * ```"x"```: number JSON data type. Represents the X coordinate of the Top Left corner of a a rectangle.
    * ```"y"```: number JSON data type. Represents the Y coordinate of the Top Left corner of a a rectangle.
     * ```"w"```: number JSON data type, must not be a negative number. Represents the width of the rectangle.
     * ```"h"```: number JSON data type, must not be a negative number. Represents the height of the rectangle.

The following is an example of a valid JSON input:
```json
{ 
    "rects": [ 
        {"x": 100, "y": 100, "w": 250, "h": 80 },  
        {"x": 120, "y": 200, "w": 250, "h": 150 },  
        {"x": 140, "y": 160, "w": 250, "h": 100 },  
        {"x": 160, "y": 140, "w": 350, "h": 190 } 
    ] 
} 
```

The **second argument** is **optional**. It will modify the maximum number of rectangles that will considered from the input. It must be a non-negative number.

The **default value** for this limit is set to 10 retangles. The optional second argument can serve to either increase or decrease this limit:
* If a valid JSON file that describes 10 rectangles is provided, but this argument is set to 5, only the first 5 rectangles from the file will be considered for calculations.
* If a valid JSON file that describes 15 rectangles is provided, but  this argument is omitted, only the first 10 rectangles will be considered, as that is the default limit.
* Any number of rectangles provided between 0 and 10 will be considered if the argument is omitted.

Here's an example of the expected usage and output for the JSON file described in this section above.

Asssuming that the file ```example.json``` is placed in the root directory of the repository:
```bash
./rectangle_intersect example.json 
Input:
   1: Rectangle at (100,100), w=250, h=80
   2: Rectangle at (120,200), w=250, h=150
   3: Rectangle at (140,160), w=250, h=100
   4: Rectangle at (160,140), w=350, h=190

Intersections:
   Between rectangles 1 and 3 at (140, 160) w=210, h=20
   Between rectangles 1 and 4 at (160, 140) w=190, h=40
   Between rectangles 2 and 3 at (140, 200) w=230, h=60
   Between rectangles 2 and 4 at (160, 200) w=210, h=130
   Between rectangles 3 and 4 at (160, 160) w=230, h=100
   Between rectangles 1, 3 and 4 at (160, 160) w=190, h=20
   Between rectangles 2, 3 and 4 at (160, 200) w=210, h=60
```
And if you decide to use the optional argument to lower the number of considered rectangles:
```bash
./rectangle_intersect example.json 3 
Input:
   1: Rectangle at (100,100), w=250, h=80
   2: Rectangle at (120,200), w=250, h=150
   3: Rectangle at (140,160), w=250, h=100

Intersections:
   Between rectangles 1 and 3 at (140, 160) w=210, h=20
   Between rectangles 2 and 3 at (140, 200) w=230, h=60
```
### Running the Tests
If the project was built using the steps from [Build with Tests](#build-with-tests), here's how to run these tests.

From the root directory of the repository:
```bash
cd build
ctest .
```