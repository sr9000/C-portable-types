# CMake version
cmake_minimum_required (VERSION 3.5)

if(TARGET blob-serialization)
	return()
endif(TARGET blob-serialization)

# project name
project (blob-serialization)

set (CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
add_subdirectory (../../integer-serialization/bin external-bins-001)

# *.h files directories
include_directories (../src)
include_directories (../../integer-serialization/src)

# library paths
link_directories (external-bins-001)

# library name and sources
add_library (blob-serialization STATIC
	../src/blob-serialization.c)

# linked libraries
target_link_libraries (blob-serialization integer-serialization)
