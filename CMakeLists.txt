cmake_minimum_required(VERSION 3.15)
project(RectangleIntersect VERSION 1.0 LANGUAGES CXX)

# Enforce C++ 23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
include(CTest)

# Set up dependencies using FetchContent
include(FetchContent)

# nlohmann::json (header-only)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0 
)

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(json googletest)

# Main executable
add_executable(rectangle_intersect src/main.cpp)

# Link nlohmann::json (header-only)
target_link_libraries(rectangle_intersect PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(rectangle_intersect PRIVATE include)

# Main executable install rules
#install(TARGETS rectangle_intersect RUNTIME DESTINATION ".")

# Test executable
add_executable(tests test/testMain.cpp)
target_link_libraries(tests PRIVATE gtest_main nlohmann_json::nlohmann_json)
include(GoogleTest)
gtest_discover_tests(tests)


