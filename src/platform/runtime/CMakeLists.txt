cmake_minimum_required (VERSION 3.8)

project("runtime")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "runtime_file_io.h"	"runtime_file_io.cpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
