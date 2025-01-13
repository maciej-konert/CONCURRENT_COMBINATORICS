#pragma once

#include <stdatomic.h>
#include <stdlib.h>

#include "common/io.h"
#include "common/sumset.h"

#define POOL_SIZE 256

#define CHECK_MALLOC(ptr) \
    do { \
        if ((ptr) == NULL) { \
            exit(1); \
        } \
    } while (0)

typedef struct shared_ptr
{
    atomic_int ref_count;
    Sumset sumset;
    struct shared_ptr* parent;
    struct shared_ptr* next;    // Used for linked list malloc implementation.
} shared_ptr;

// SHARED_PTR FOOS

void init_shared_ptr(shared_ptr** ptr, Sumset sumset) {
    *ptr = malloc(sizeof(shared_ptr));
    CHECK_MALLOC(*ptr);

    (*ptr)->ref_count = 1;
    (*ptr)->parent = NULL;
    (*ptr)->sumset = sumset;
}

shared_ptr* alloc_ptr(shared_ptr** ptrPool)
{
    if (!*ptrPool) {
        shared_ptr* prev = malloc(sizeof(struct shared_ptr));
        CHECK_MALLOC(prev);
        *ptrPool = prev;

        for (int i = 0; i < POOL_SIZE; i++) {
            prev->next = malloc(sizeof(struct shared_ptr));
            CHECK_MALLOC(prev->next);
            prev = prev->next;
            prev->next = NULL;
        }
    }

    shared_ptr* ptr = *ptrPool;
    *ptrPool = (*ptrPool)->next;

    return ptr;
}

void release_ptr(shared_ptr* ptr, shared_ptr** ptrPool)
{
    while (ptr && --ptr->ref_count == 0) {
        shared_ptr* tmp = ptr->parent;

        ptr->next = *ptrPool;
        *ptrPool = ptr;
        ptr = tmp;
    }
}

// POOL CREATION

void init_pool(shared_ptr** ptr_pool)
{
    *ptr_pool = malloc(sizeof(shared_ptr));
    CHECK_MALLOC(*ptr_pool);

    shared_ptr* prev = *ptr_pool;
    for (int i = 0; i < POOL_SIZE; i++) {
        prev->next = malloc(sizeof(shared_ptr));
        CHECK_MALLOC(prev->next);

        prev = prev->next;
        prev->next = NULL;
    }
}

void destroy_pool(shared_ptr* ptr_pool)
{
    shared_ptr* prev = ptr_pool;
    while (prev) {
        shared_ptr *tmp = prev->next;
        free(prev);
        prev = tmp;
    }
}
