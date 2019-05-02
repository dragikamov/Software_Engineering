# Making sure that the version of cmake we are using is correct
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Creating the project and specifying the languages it will be run on
project(PencilProducer LANGUAGES CXX)

# This puts our created ui_mainwindow file in the source directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Adding the qt packages to the cmake build
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

# Populate a CMake variable with the sources
set(project_SRCS
    mainwindow.ui
    main.cpp
    mainwindow.cpp)

# Creating the executable from the source and header files
add_executable(${PROJECT_NAME} ${project_SRCS})

# Linking our libraries to our executable. That is, including all the
# Qt libraries we will use
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Network)
