# Making sure that the version of cmake we are using is correct
cmake_minimum_required(VERSION 3.1.0)

# Creating the project and specifying the languages it will be run on
project(pencil_producer LANGUAGES CXX)

# Setting the Qt environment
if(EXISTS $ENV{HOME}/Qt/5.13.0/gcc_64)
  set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.13.0/gcc_64)
else()
  set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.12.2/gcc_64)
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall")

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

# Populate a CMake variable with the sources
set(PencilProducer_SRCS
    window.ui
    window.cpp
    main.cpp
    wallet.cpp
    inventory.cpp
    api.cpp
)

# Tell CMake to create the Pencil Universe executable
add_executable(PencilProducer ${PencilProducer_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(PencilProducer ${SRC_LIBRARIES})
