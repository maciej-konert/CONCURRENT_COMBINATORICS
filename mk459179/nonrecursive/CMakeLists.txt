cmake_minimum_required(VERSION 3.12)

add_executable(nonrecursive main.c)
target_link_libraries(nonrecursive io err)
