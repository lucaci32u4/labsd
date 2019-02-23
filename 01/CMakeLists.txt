cmake_minimum_required(VERSION 3.13)
project(01 C)

set(CMAKE_C_STANDARD 99)

add_executable(charTest charTest.c OrderedSet.h)
add_executable(longTest longTest.c OrderedSet.h)
