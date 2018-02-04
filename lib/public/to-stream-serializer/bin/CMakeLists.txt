# CMake version
cmake_minimum_required (VERSION 3.5)

if (TARGET to-stream-serializer)
	return ()
endif (TARGET to-stream-serializer)

# project name
project (to-stream-serializer)

set (CMAKE_C_STANDARD 11)

# *.h files directories
include_directories (../src)

# library name and sources
add_library (to-stream-serializer STATIC ../src/to-stream-serializer.c)
