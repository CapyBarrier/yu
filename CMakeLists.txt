cmake_minimum_required(VERSION 4.3.0)
project(Yu CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++23 -Wall -Wextra")

add_subdirectory(docs/)

add_subdirectory(tests/tuples)