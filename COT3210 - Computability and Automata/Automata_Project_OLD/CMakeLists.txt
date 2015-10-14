cmake_minimum_required(VERSION 3.1)
project(Automata_Project_Linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Cell.cpp Cell.h)
add_executable(Automata_Project_Linux ${SOURCE_FILES})