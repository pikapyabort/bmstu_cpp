cmake_minimum_required(VERSION 3.24)
project(iostream_and_stl)

set(CMAKE_CXX_STANDARD 20)

add_executable(iostream_and_stl main.cpp
        first_part/data.h
        first_part/application_first.h
        first_part/application_first.cpp
        second_part/subject_manager.h
        second_part/second_part_application.h
        second_part/subject.h
        second_part/subject_manager.cpp
        second_part/second_part_application.cpp first_part/data.cpp)
