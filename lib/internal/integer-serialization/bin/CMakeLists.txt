# CMake version
cmake_minimum_required (VERSION 3.5)

if (TARGET integer-serialization)
	return ()
endif (TARGET integer-serialization)

# project name
project (integer-serialization)

set (CMAKE_C_STANDARD 11)

# *.h files directories
include_directories (../src)

# library name and sources
add_library (integer-serialization STATIC ../src/integer-serialization.c)
