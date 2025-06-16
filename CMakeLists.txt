cmake_minimum_required(VERSION 3.10)
project(loggr VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set output directory for the final executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# add the executable (include main.cpp explicitly)
add_executable(loggr main.cpp ${SOURCES})

# Include header files from include/ directory
target_include_directories(loggr PRIVATE ${CMAKE_SOURCE_DIR}/include)

# install step for `make install`
install(TARGETS loggr DESTINATION bin)
