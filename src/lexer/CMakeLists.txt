cmake_minimum_required (VERSION 3.8)

project("lexer")

# Add source to this project's executable.
add_library(${PROJECT_NAME} lexer.h			  lexer.cpp 
							token.h			  token.hpp 
							token_generator.h token_generator.cpp 
							symbol.h 
							keyword.h 
							regex.cpp)

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif(WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC ../)
