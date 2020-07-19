cmake_minimum_required (VERSION 3.8)

project("util")

# Add source to this project's executablj.
add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/id_generator.hpp ${CMAKE_CURRENT_SOURCE_DIR}/type_id_generator.hpp)
