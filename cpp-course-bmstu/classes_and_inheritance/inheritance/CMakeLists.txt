cmake_minimum_required(VERSION 3.23)
project(inheritance)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(inheritance
        currency.cpp
        currency.h
        main.cpp
        applicaton.cpp
        applicaton.h
        euro.cpp
        euro.h
        dollar.cpp
        dollar.h)
