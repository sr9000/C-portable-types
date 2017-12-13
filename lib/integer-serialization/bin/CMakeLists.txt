# CMake version
cmake_minimum_required (VERSION 3.5)

# project name
project (integer-serialization)

# *.h files directories
include_directories (../src)

# library name and sources
add_library (integer-serialization STATIC ../src/integer-serialization.c)
