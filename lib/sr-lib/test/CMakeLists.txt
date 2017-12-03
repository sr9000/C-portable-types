# CMake version
cmake_minimum_required (VERSION 2.6)

# project name
project (sr-lib-flow-control-test)

# *.h files directories
include_directories(../src)

# library paths
link_directories(../bin)

# main goal
add_executable(main main.c)

# linked libraries
target_link_libraries(main sr-lib-flow-control)
