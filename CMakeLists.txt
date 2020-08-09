# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("rogue")

# Include sub-projects.
add_subdirectory ("src")

if(WIN32)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif(WIN32)
