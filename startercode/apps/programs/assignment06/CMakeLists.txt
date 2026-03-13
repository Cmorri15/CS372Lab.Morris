cmake_minimum_required(VERSION 3.5)
project(assignment06)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executable for dictionary test
add_executable(dictionarytest dictionarytest.cpp)