cmake_minimum_required(VERSION 3.24)
project(mesh_loader)

set(CMAKE_CXX_STANDARD 23)

add_executable(mesh_loader main.cpp  MeshLoader.h MeshLoader.cpp DataStructures.h DataStructures.cpp Exception.h AneuMeshLoader.cpp AneuMeshLoader.h)
