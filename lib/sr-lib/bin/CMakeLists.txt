# CMake version
cmake_minimum_required (VERSION 2.6)

# project name
project (sr-lib-flow-control)

# *.h files directories
include_directories(../src)

# library name and sources
add_library(sr-lib-flow-control STATIC ../src/flow-control.c)
