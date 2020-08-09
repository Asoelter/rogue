cmake_minimum_required (VERSION 3.8)

project("util")

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/id_generator.hpp 
										 ${CMAKE_CURRENT_SOURCE_DIR}/type_id.hpp
										 ${CMAKE_CURRENT_SOURCE_DIR}/file_io.h
										 ${CMAKE_CURRENT_SOURCE_DIR}/allocator.h)

target_include_directories(${PROJECT_NAME} INTERFACE ../)
