cmake_minimum_required(VERSION 3.15)
project(RectangleIntersect VERSION 1.0 LANGUAGES CXX)

# Cmake Environment Vars
option(INSTALL_GTEST OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

## Project Definitions
set(INCLUDE_DIR include)
set(SRC_DIR src)
set(TEST_DIR test)
set(MAIN_EXECUTABLE_NAME rectangle_intersect)
set(TEST_EXECUTABLE_NAME tests)

## Enforce C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch Dependencies
include(FetchContent)

## nlohmann::json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0  #TODO: replace with commit hash, dependency lock
  # TODO: see if can find_package_args
)
FetchContent_MakeAvailable(json)

if(ENABLE_TESTS)
  ## GoogleTest
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0 #TODO: dependency lock
    FIND_PACKAGE_ARGS NAMES GTest
  )
  FetchContent_MakeAvailable(googletest)
endif()

# Main executable
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
add_executable(${MAIN_EXECUTABLE_NAME} ${SRC_FILES})
## Main executable header files
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
set_target_properties(${MAIN_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json) #TODO: check if json needs to be linked since its header only

# Testing
if(ENABLE_TESTS)
  include(CTest)
  include(GoogleTest)

  ## Test Files
  file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
  set(TEST_SRC_FILES ${SRC_FILES})
  list(REMOVE_ITEM TEST_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/Main.cpp")

  ## Test Executable
  # TODO: if mocks are needed, swap to an approach witth multiple test executables
  # and replace the source files of the mocked classes for that particular test suite
  add_executable(${TEST_EXECUTABLE_NAME} ${TEST_FILES} ${TEST_SRC_FILES}) 
  target_compile_definitions(${TEST_EXECUTABLE_NAME} PRIVATE TEST)
  target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
  target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE gtest_main nlohmann_json::nlohmann_json)
  gtest_discover_tests(${TEST_EXECUTABLE_NAME})
endif()

