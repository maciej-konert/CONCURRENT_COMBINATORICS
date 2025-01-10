add_executable(parallel main.c
        stack.h
        shared_ptr.h)
target_link_libraries(parallel io err atomic)
