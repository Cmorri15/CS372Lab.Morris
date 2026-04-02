cmake_minimum_required(VERSION 3.5)
project(assignment08)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executables
add_executable(simplecycletest simplecycletest.cpp)
add_executable(kevinbacontest kevinbacontest.cpp)