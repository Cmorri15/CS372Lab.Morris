cmake_minimum_required(VERSION 3.5)
project(assignment02)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files from the include directory
include_directories(../../../include)

# Create executables for each timing program
add_executable(vectortime vectortime.cpp)
add_executable(vectorcopy vectorcopy.cpp)
add_executable(vectoropt vectoropt.cpp)