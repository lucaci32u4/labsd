cmake_minimum_required(VERSION 3.13)
project(06 C)

set(CMAKE_C_STANDARD 99)

add_executable(BSTList BSTList.c BST.h Queue.h List.h)
add_executable(testBST testBST.c BST.h)
