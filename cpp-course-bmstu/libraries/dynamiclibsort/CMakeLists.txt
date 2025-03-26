cmake_minimum_required(VERSION 3.17)
project(dynamiclibsort)

set(CMAKE_CXX_STANDARD 14)

add_library(dynamiclibsort SHARED dynamiclibsort.cpp dynamiclibsort.h)
target_include_directories (dynamiclibsort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(dynamiclibsort PROPERTIES PUBLIC_HEADER libraries/dynamiclibsort.h)
