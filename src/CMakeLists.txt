# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (rogue  main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(DEBUG=1)
else()
	message("Compile definition is " + ${CMAKE_CONFIGURATION_TYPES})
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

if(WIN32)
	add_compile_definitions(ROGUE_PLATFORM_WINDOWS=1)
elseif(UNIX AND NOT APPLE)
    add_definitions(-DROGUE_PLATFORM_LINUX)
elseif(APPLE)
	add_definitions(-DROGUE_PLATFORM_MAC)
else()
	add_definitions(-DROGUE_PLATFORM_RUNTIME)
endif(WIN32)

add_compile_definitions(ROGUE_RESOURCE_DIRECTORY="res")

function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

addDirectory(containers)
addDirectory(lexer)
addDirectory(parser)
addDirectory(util)
addDirectory(platform)
addDirectory(grammar)

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif(WIN32)
