cmake_minimum_required(VERSION 3.10)
project(Practica3_CC232)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main demos/main.cpp src/SlidingWindow.cpp)

add_executable(test_pc3 tests/test.cpp src/SlidingWindow.cpp)