cmake_minimum_required (VERSION 3.8)

project("parser")

# Add source to this project's executable.
add_library(${PROJECT_NAME} parser.h parser.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC ../)
