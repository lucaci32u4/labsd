cmake_minimum_required(VERSION 3.13)
project(12 C)

set(CMAKE_C_STANDARD 99)

add_executable(Words words.c)

configure_file(fileA fileA COPYONLY)
configure_file(fileB fileB COPYONLY)