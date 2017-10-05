cmake_minimum_required(VERSION 3.5)
project(isa)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c instructions/add.c instructions/cmp.c instructions/mov.c instructions/jmp.c)
add_executable(isa ${SOURCE_FILES})