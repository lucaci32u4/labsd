project(02 C)

set(CMAKE_C_STANDARD 99)

add_executable(testSortedList SortedList.h testSortedList.c)

add_executable(length length.c)

add_executable(eratostene SortedList.h eratostene.c)
target_link_libraries(eratostene m)

