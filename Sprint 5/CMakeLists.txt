# Making sure that the version of cmake we are using is correct
cmake_minimum_required(VERSION 3.1.0)

# Creating the project and specifying the languages it will be run on
project(pencil_producer LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++0x -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Listing all the directories
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)

