# CMake version
cmake_minimum_required (VERSION 3.5)

if (TARGET to-stream-serializer)
	return ()
endif (TARGET to-stream-serializer)

# project name
project (to-stream-serializer)

set (CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
add_subdirectory (../../../internal/sr-lib-flow-control/bin external-bins-001)

# *.h files directories
include_directories (
	../src
	../../../internal/sr-lib-flow-control/src)

# library paths
link_directories (external-bins-001)

# library name and sources
add_library (to-stream-serializer STATIC ../src/to-stream-serializer.c)

# linked libraries
target_link_libraries (to-stream-serializer sr-lib-flow-control)
