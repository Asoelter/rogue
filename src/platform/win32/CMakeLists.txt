cmake_minimum_required (VERSION 3.8)

project("win32")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "win32.h"
							win32_file_io.h win32_file_io.cpp)
