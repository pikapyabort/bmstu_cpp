cmake_minimum_required(VERSION 3.20)
project(classes_and_inheritance)


set(CMAKE_CXX_STANDARD 20)

add_executable(classes_and_objects main.cpp
                                    calculator.cpp calculator.h
                                    fraction.cpp fraction.h
                                    application.cpp application.h)
