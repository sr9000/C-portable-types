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
add_subdirectory (
	../../../internal/integer-serialization/bin
	external-bins-002)
add_subdirectory (
	../../../internal/floating-point-serialization/bin
	external-bins-003)
add_subdirectory (../../../internal/blob-serialization/bin external-bins-004)

# *.h files directories
include_directories (
	../src
	../../../internal/sr-lib-flow-control/src
	../../../internal/integer-serialization/src
	../../../internal/floating-point-serialization/src
	../../../internal/blob-serialization/src)

# library paths
link_directories (external-bins-001)
link_directories (external-bins-002)
link_directories (external-bins-003)
link_directories (external-bins-004)

# library name and sources
add_library (to-stream-serializer STATIC ../src/to-stream-serializer.c)

# linked libraries
target_link_libraries (
	to-stream-serializer
	sr-lib-flow-control
	integer-serialization
	floating-point-serialization
	blob-serialization)
