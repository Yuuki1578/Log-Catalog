cmake_minimum_required (VERSION 3.20)
project (lc VERSION 1.0)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED TRUE)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable (lc main.c)
