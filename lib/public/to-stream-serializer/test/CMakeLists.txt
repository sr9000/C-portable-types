# CMake version
cmake_minimum_required (VERSION 3.5)

macro(link_extern dir)
	string(REGEX REPLACE "[\\\\/.]" "_" tmp ${dir})
	add_subdirectory (${dir} ${tmp})
	link_directories (${tmp})
endmacro(link_extern)

set (PRJ "to-stream-serializer-test")

if (TARGET ${PRJ})
	return ()
endif (TARGET ${PRJ})

# project name
project (${PRJ})

set (CMAKE_C_STANDARD 11)

# dependency. put resulting binaries into local directory
link_extern (../bin)
link_extern (../../../internal/sr-lib-flow-control/bin)

# *.h files directories
include_directories (
	../../../c-test-macroses/src
	${include_direcroties_list}
)

# main goal
add_executable (main.exe main.c)

# linked libraries
target_link_libraries (main.exe ${target_link_libraries_list})
