
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project("SOM")

find_package(OpenGL REQUIRED)
find_package(OpenMP)

add_subdirectory(extern)
add_subdirectory(src)