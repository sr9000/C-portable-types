# CMake version
cmake_minimum_required (VERSION 3.5)

# project name
project (sr-lib-flow-control)

set(CMAKE_C_STANDARD 11)

# *.h files directories
include_directories (../src)

# library name and sources
add_library (sr-lib-flow-control STATIC ../src/flow-control.c)
