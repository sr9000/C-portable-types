# CMake version
cmake_minimum_required (VERSION 3.5)

set (PRJ "flow-control")

if (TARGET ${PRJ})
	return ()
endif (TARGET ${PRJ})

# project name
project (${PRJ})

set (CMAKE_C_STANDARD 11)

# compute path to sources
get_filename_component (sources ../src ABSOLUTE)

# append include directories list
list (APPEND include_direcroties_list ${sources})

# *.h files directories
include_directories (${include_direcroties_list})

# library name and sources
add_library (${PROJECT_NAME} STATIC ../src/${PROJECT_NAME}.c)

# append extern binaries and target link libraries lists simultaneously
list (APPEND target_link_libraries_list ${PROJECT_NAME})

# save local scope to parent scope
get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
	set(include_direcroties_list "${include_direcroties_list}" PARENT_SCOPE)
	set(target_link_libraries_list "${target_link_libraries_list}" PARENT_SCOPE)
endif ()
