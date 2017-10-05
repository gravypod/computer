cmake_minimum_required(VERSION 3.8)
project(isa)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c instructions/add.c)
add_executable(isa ${SOURCE_FILES})