#
# CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.1.0)
project(Pencils)

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME misc COMMAND test-pencils)
