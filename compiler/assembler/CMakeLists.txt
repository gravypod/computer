cmake_minimum_required(VERSION 3.5)
project(assembler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES main.cpp
        instructions.h
        tokens/token.h tokens/label/creation.h tokens/label/reference.h tokens/register.h tokens/literal.h tokens/op.h)
add_executable(assembler ${SOURCE_FILES})
