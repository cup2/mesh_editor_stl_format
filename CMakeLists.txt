cmake_minimum_required(VERSION 3.10)
project(ExampleProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(mesh)

add_subdirectory(mesh)
add_subdirectory(test)
add_subdirectory(external/googletest)
