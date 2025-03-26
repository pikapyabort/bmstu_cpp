cmake_minimum_required(VERSION 3.21)
project(stl)

set(CMAKE_CXX_STANDARD 20)

include_directories(stl)

add_executable(stl
        stl/Algorithms.h
        stl/Container.h
        stl/Exceptions.h
        stl/Iterator.h
        stl/Main.cpp)
