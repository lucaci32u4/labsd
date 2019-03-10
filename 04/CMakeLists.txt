cmake_minimum_required(VERSION 3.13)
project(04 C)

set(CMAKE_C_STANDARD 99)

add_executable(parantheses parantheses.c Stack.h)
add_executable(radix_sort radix_sort.c Queue.h)
add_executable(testStack testStack Stack.h)
add_executable(testQueue testQueue.c Queue.h)

target_link_libraries(parantheses m)
target_link_libraries(radix_sort m)
target_link_libraries(testStack m)
target_link_libraries(testQueue m)

configure_file(input-parantheses.txt input-parantheses.txt COPYONLY)
configure_file(input-radix-sort.csv input-radix-sort.csv COPYONLY)