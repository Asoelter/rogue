cmake_minimum_required (VERSION 3.8)

project("lexer")

# Add source to this project's executable.
add_library(${PROJECT_NAME} lexer.h			  lexer.cpp 
							token.h			  token.hpp 
							token_generator.h token_generator.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../)
