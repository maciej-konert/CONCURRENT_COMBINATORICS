#pragma once

#include <stdio.h>
#include "shared_ptr.h"

#define STACK_SIZE 2048

typedef struct foo_call {
    shared_ptr *a;
    shared_ptr *b;
} Foo_call;

typedef struct stack {
   Foo_call *array;
   atomic_int capacity;
   int max_capacity;
} Stack;

// FOOCALL FOOS

void swap(Foo_call *f)
{
    if (f->a->sumset.sum > f->b->sumset.sum) {
        shared_ptr* ptr = f->a;
        f->a = f->b;
        f->b = ptr;
    }
}

// STACK FOOS

void init_stack(Stack** stack)
{
    Stack* new_stack = malloc(sizeof(Stack));
    Foo_call* arr = malloc(STACK_SIZE * sizeof(Foo_call));
    CHECK_MALLOC(new_stack);
    CHECK_MALLOC(arr);

    new_stack->capacity = 0;
    new_stack->array = arr;
    new_stack->max_capacity = STACK_SIZE;

    *stack = new_stack;
}

void destroy_stack(Stack* stack)
{
    free(stack->array);
    free(stack);
}

Foo_call pop(Stack* stack)
{
    assert(stack->capacity > 0);
    return stack->array[--stack->capacity];
}

void push(Stack* stack, Foo_call f)
{
    if (stack->capacity == stack->max_capacity) {
        Foo_call* new = malloc(2 * stack->max_capacity * sizeof(Foo_call));
        CHECK_MALLOC(new);

        for (int i = 0; i < stack->capacity; i++) {
            new[i] = stack->array[i];
        }
        free(stack->array);
        stack->array = new;
        stack->max_capacity = 2 * stack->max_capacity;
    }
    stack->array[stack->capacity++] = f;
}

static inline bool is_empty(const Stack* stack)
{
    return stack->capacity == 0;
}

static inline int capacity(const Stack* stack)
{
    return stack->capacity;
}