# CMake version
cmake_minimum_required (VERSION 3.5)

# project name
project (sr-lib-flow-control-test)

# dependency. put resulting binaries into local directory
add_subdirectory (../bin external-bins)

# *.h files directories
include_directories (../src)

# library paths
link_directories (external-bins)

# main goal
add_executable (main.exe main.c)

# linked libraries
target_link_libraries (main.exe sr-lib-flow-control)
