cmake_minimum_required(VERSION 3.14)
project(11 C)

set(CMAKE_C_STANDARD 99)

add_executable(Graph graph.c heap.h MinHeap.h)

configure_file(graph.in graph.in COPYONLY)