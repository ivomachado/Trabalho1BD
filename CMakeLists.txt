cmake_minimum_required(VERSION 3.10)

# Project name
project(Trabalho1BD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -g2")

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE TEST_SRCS "tests/*.cpp")

# Object files output directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main executable
add_executable(program ${SRCS})
list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/program.cpp")

# Test executable
add_executable(check ${TEST_SRCS} ${SRCS})
