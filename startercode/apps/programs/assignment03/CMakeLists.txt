cmake_minimum_required(VERSION 3.5)
project(assignment03)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executable for list test
add_executable(listtest listtest.cpp)
add_executable(bagtest bagtest.cpp)
add_executable(circularlisttest circularlisttest.cpp)