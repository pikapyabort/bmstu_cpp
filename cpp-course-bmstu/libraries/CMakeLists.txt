cmake_minimum_required(VERSION 3.20)
project(libraries)


include_directories(staticlibsort)
include_directories(dynamiclibsort)

add_subdirectory(staticlibsort)
add_subdirectory(dynamiclibsort)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(libraries main.cpp staticlibsort/staticlibsort.cpp staticlibsort/staticlibsort.h
        dynamiclibsort/dynamiclibsort.cpp dynamiclibsort/dynamiclibsort.h)

target_link_libraries(libraries dynamiclibsort)
target_link_libraries(libraries staticlibsort)
