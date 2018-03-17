# CMake version
cmake_minimum_required (VERSION 3.5)

# project name
project (sr-lib-flow-control-test)

set (CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
add_subdirectory (../bin library-binary)

# *.h files directories
include_directories (${include_direcroties_list})

# library paths
link_directories (library-binary)

# main goal
add_executable (main.exe main.c)

# linked libraries
target_link_libraries (main.exe ${target_link_libraries_list})
