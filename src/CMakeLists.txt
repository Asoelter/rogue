# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (rogue  main.cpp "parser/parser.h" "parser/parser.cpp" "parser/namespace.h")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(DEBUG=1)
else()
	message("Compile definition is " + ${CMAKE_CONFIGURATION_TYPES})
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

if(WIN32)
	add_compile_definitions(ROGUE_PLATFORM_WINDOWS=1)
endif(WIN32)

function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

addDirectory(lexer)
addDirectory(parser)
addDirectory(util)
addDirectory(platform)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)