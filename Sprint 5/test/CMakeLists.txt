cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_SOURCE_DIR})

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Add curl libraries
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# Add JSON libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(SRC_LIBRARIES
    ${CURL_LIBRARIES}
    ${JSONCPP_LIBRARIES}
    Qt5::Widgets)

set(TEST_LIBRARIES
    ${SRC_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread)

set(runTest_SRCS
    ../src/window.h
    ../src/wallet.h
    ../src/wallet.cpp
    ../src/inventory.h
    ../src/inventory.cpp
    window_test.cpp
    ../src/api.cpp
)

#Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${runTest_SRCS})
target_link_libraries(runTests ${TEST_LIBRARIES})
