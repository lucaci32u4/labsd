cmake_minimum_required(VERSION 3.13)
project(03 C)

set(CMAKE_C_STANDARD 99)

add_executable(problem problem.c DoubleLinkedList.h)
add_executable(example example.c DoubleLinkedList.h)
add_executable(testList testList.c DoubleLinkedList.h)

configure_file(input input COPYONLY)