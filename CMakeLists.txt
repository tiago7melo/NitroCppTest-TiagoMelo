cmake_minimum_required(VERSION 3.15)
project(RectangleIntersect VERSION 1.0 LANGUAGES CXX)

# Cmake Environment Vars
set(INSTALL_GTEST OFF CACHE BOOL "Do not install GTest" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "Install exec in root folder" FORCE)

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

# Check for Compiler Compatibility
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++23" COMPILER_SUPPORTED)

if(NOT COMPILER_SUPPORTED)
  message(FATAL_ERROR "The compiler does not support C++23.")
endif()

# Fetch Dependencies
include(FetchContent)

## nlohmann::json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0 
)
FetchContent_MakeAvailable(json)

## GoogleTest
if(ENABLE_TESTS)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
  )
  FetchContent_MakeAvailable(googletest)
endif()

# Main executable
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
add_executable(${MAIN_EXECUTABLE_NAME} ${SRC_FILES})
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/main.cpp")
## Main executable header files
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
## Link nlohmann::json (header-only)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

## Main executable install rules
install(TARGETS ${MAIN_EXECUTABLE_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})

# Testing
if(ENABLE_TESTS)
  include(CTest)
  
  ## Test executable
  file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
  # TODO: not compatible with mocks if I need to do that eventually
  #       will need to specifically add the file we want to test by name if we want to mock the others
  add_executable(${TEST_EXECUTABLE_NAME} ${TEST_FILES} ${SRC_FILES}) 
  target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
  target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE gtest_main nlohmann_json::nlohmann_json)
  include(GoogleTest)
  gtest_discover_tests(${TEST_EXECUTABLE_NAME})
endif()


