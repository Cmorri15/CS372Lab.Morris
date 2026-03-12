cmake_minimum_required(VERSION 3.5)
project(assignment05)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executable for smart pointer list test
add_executable(listsmartptrtest listsmartptrtest.cpp)
add_executable(treesmartptrtest treesmartptrtest.cpp)
add_executable(treetraversalstest treetraversalstest.cpp)