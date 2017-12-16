# CMake version
cmake_minimum_required (VERSION 3.5)

# project name
project (floating-point-serialization-test)

set(CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
add_subdirectory (../bin external-bins-001)
add_subdirectory (../../sr-lib-flow-control/bin external-bins-002)

# *.h files directories
include_directories (
	../src
	../../c-test-macroses/src
	../../sr-lib-flow-control/src
	../../integer-serialization/src)

# library paths
link_directories (external-bins-001)
link_directories (external-bins-002)

# main goal
add_executable (main.exe main.c)

# linked libraries
target_link_libraries (main.exe
	floating-point-serialization
	sr-lib-flow-control
	m) # math library
