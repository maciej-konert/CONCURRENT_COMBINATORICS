cmake_minimum_required(VERSION 3.12)

add_executable(parallel main.c
        stack.h
        shared_ptr.h)
target_link_libraries(parallel io err)
