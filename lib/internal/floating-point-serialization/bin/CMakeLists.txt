# CMake version
cmake_minimum_required (VERSION 3.5)

if(TARGET floating-point-serialization)
	return()
endif(TARGET floating-point-serialization)

# project name
project (floating-point-serialization)

set(CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
add_subdirectory (../../integer-serialization/bin external-bins-001)

# *.h files directories
include_directories (../src)
include_directories (../../integer-serialization/src)

# library paths
link_directories (external-bins-001)

# library name and sources
add_library (floating-point-serialization STATIC
	../src/floating-point-serialization.c)

# linked libraries
target_link_libraries (floating-point-serialization integer-serialization)
