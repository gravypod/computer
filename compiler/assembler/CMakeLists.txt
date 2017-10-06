cmake_minimum_required(VERSION 3.5)
project(assembler)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ops.h arguments.c arguments.h convert.c convert.h)
add_executable(assembler ${SOURCE_FILES})