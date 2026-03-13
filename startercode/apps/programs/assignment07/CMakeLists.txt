cmake_minimum_required(VERSION 3.5)
project(assignment07)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executable for tree comparison
add_executable(treecomparison treecomparison.cpp)