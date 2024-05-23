cmake_minimum_required(VERSION 3.27)
project(Campo_minato)

set(CMAKE_CXX_STANDARD 17)

add_executable(Campo_minato main.cpp
        ../headers/field.hpp
        ../src/field.cpp)
