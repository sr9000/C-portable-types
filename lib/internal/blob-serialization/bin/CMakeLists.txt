# CMake version
cmake_minimum_required (VERSION 3.5)

macro(link_extern dir)
	string(REGEX REPLACE "[\\\\/.]" "_" tmp ${dir})
	add_subdirectory (${dir} ${tmp})
	link_directories (${tmp})
endmacro(link_extern)

set (PRJ "blob-serialization")

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

# dependency. put resulting binaries into local directory
link_extern (../../integer-serialization/bin)

# *.h files directories
include_directories (${include_direcroties_list})

# library name and sources
add_library (${PROJECT_NAME} STATIC ../src/${PROJECT_NAME}.c)

# linked libraries
target_link_libraries (${PROJECT_NAME} ${target_link_libraries_list})

# append target link libraries lists with current lib
list (APPEND target_link_libraries_list ${PROJECT_NAME})

# save local scope to parent scope
get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
	set(include_direcroties_list "${include_direcroties_list}" PARENT_SCOPE)
	set(target_link_libraries_list "${target_link_libraries_list}" PARENT_SCOPE)
endif ()
