# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (rogue  main.cpp)

if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
	add_compile_definitions(DEBUG=1)
endif(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")

function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

addDirectory(lexer)
addDirectory(util)
addDirectory(platform)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)