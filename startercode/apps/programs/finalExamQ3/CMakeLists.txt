cmake_minimum_required(VERSION 3.5)
project(finalExamQ3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../../include)

add_executable(floydtest floydtest.cpp)