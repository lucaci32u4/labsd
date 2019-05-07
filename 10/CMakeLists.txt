cmake_minimum_required(VERSION 3.13)
project(10 C)

set(CMAKE_C_STANDARD 99)

add_executable(TestGraph testGraph.c Util.c Util.h Graph.c Graph.h)

configure_file(graph.in graph.in COPYONLY)