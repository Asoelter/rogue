cmake_minimum_required (VERSION 3.8)

project("linux")

# Add source to this project's executable.
add_library(${PROJECT_NAME}     "linux_file_io.h"	"linux_file_io.cpp")
    #"linux_allocator.h"	"linux_allocator.cpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
