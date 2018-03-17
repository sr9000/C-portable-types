# CMake version
cmake_minimum_required (VERSION 3.5)

macro(link_extern dir)
	string(REGEX REPLACE "[\\\\/.]" "_" tmp ${dir})
	add_subdirectory (${dir} ${tmp})
	link_directories (${tmp})
endmacro(link_extern)

set (PRJ "to-stream-serializer")

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
link_extern (../../../internal/sr-lib-flow-control/bin)
link_extern (../../../internal/integer-serialization/bin)
link_extern (../../../internal/floating-point-serialization/bin)
link_extern (../../../internal/blob-serialization/bin)

# *.h files directories
include_directories (${include_direcroties_list})

# library name and sources
add_library (${PROJECT_NAME} STATIC ../src/${PROJECT_NAME}.c)

# linked libraries
# math library also needed
target_link_libraries (${PROJECT_NAME} ${target_link_libraries_list})

# append target link libraries lists with current lib
list (APPEND target_link_libraries_list ${PROJECT_NAME})

# save local scope to parent scope
get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
	set(include_direcroties_list "${include_direcroties_list}" PARENT_SCOPE)
	set(target_link_libraries_list "${target_link_libraries_list}" PARENT_SCOPE)
endif ()
