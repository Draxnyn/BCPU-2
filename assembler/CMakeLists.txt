cmake_minimum_required(VERSION 3.10)
project(bcpu-asm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(bcpu-asm
src/main.cpp
src/lexer.cpp
src/parser.cpp
src/grammar.cpp
src/instruction.cpp
src/syntax.cpp
)

target_include_directories(bcpu-asm PRIVATE src/include)
