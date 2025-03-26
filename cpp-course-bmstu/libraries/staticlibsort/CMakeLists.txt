cmake_minimum_required(VERSION 3.17)
project(staticlibsort)

set(CMAKE_CXX_STANDARD 14)

add_library(staticlibsort STATIC staticlibsort.cpp staticlibsort.h)
