#
# /test/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Find the QtTest library
find_package(Qt5 COMPONENTS Test Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(Test_SRCS
    test.cpp
)

set(Pencil_SRCS
    ../src/pencilproducer.cpp
    ../src/pencilproducer.ui
)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

add_executable(test-pencils ${Test_SRCS} ${Pencil_SRCS})

# Use the Test module from Qt 5
target_link_libraries(test-pencils Qt5::Test Qt5::Widgets)
