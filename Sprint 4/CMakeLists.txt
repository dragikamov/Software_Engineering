# Making sure that the version of cmake we are using is correct
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Creating the project and specifying the languages it will be run on
project(PencilProducer LANGUAGES CXX)

# Listing all the directories
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)

