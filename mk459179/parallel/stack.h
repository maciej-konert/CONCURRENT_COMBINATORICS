#pragma once

#include "shared_ptr.h"

#define STACK_SIZE 1024

pthread_mutex_t stack_mutex;
pthread_cond_t stack_cond;
int workers_waiting = 0;
int no_threads;
bool running = true;

typedef struct foo_call {
    shared_ptr *a;
    shared_ptr *b;
} Foo_call;

typedef struct stack {
   Foo_call *array;
   atomic_int capacity;
   int max_capacity;
} Stack;

// STACK FOOS

void init_stack(Stack** stack, int t)
{
    Stack* new_stack = malloc(sizeof(Stack));
    Foo_call* arr = malloc(STACK_SIZE * sizeof(Foo_call));
    CHECK_MALLOC(new_stack);
    CHECK_MALLOC(arr);

    ASSERT_ZERO(pthread_cond_init(&stack_cond, NULL));
    ASSERT_ZERO(pthread_mutex_init(&stack_mutex, NULL));
    new_stack->capacity = 0;
    new_stack->array = arr;
    new_stack->max_capacity = STACK_SIZE;

    no_threads = t;
    *stack = new_stack;
}

void destroy_stack(Stack* stack)
{
    ASSERT_ZERO(pthread_cond_destroy(&stack_cond));
    ASSERT_ZERO(pthread_mutex_destroy(&stack_mutex));
    free(stack->array);
    free(stack);
}

bool pop(Stack* stack, Foo_call* call)
{
    if (no_threads == 1 && stack->capacity > 0) {
        *call = stack->array[--stack->capacity];
        return true;
    }
    ASSERT_ZERO(pthread_mutex_lock(&stack_mutex));
    workers_waiting++;

    if (workers_waiting == no_threads) {
        running = false;
    }
    if (stack->capacity > 0) {
        *call = stack->array[--stack->capacity];
        ASSERT_ZERO(pthread_mutex_unlock(&stack_mutex));
        return true;
    }
    while (running && stack->capacity == 0) {
        ASSERT_ZERO(pthread_cond_wait(&stack_cond, &stack_mutex));
    }
    workers_waiting--;

    if (running) {
        *call = stack->array[--stack->capacity];
        ASSERT_ZERO(pthread_mutex_unlock(&stack_mutex));
        return true;
    } else {
        ASSERT_ZERO(pthread_mutex_unlock(&stack_mutex));
        return false;
    }
}

void push(Stack* stack, Foo_call f)
{
    ASSERT_ZERO(pthread_mutex_lock(&stack_mutex));
    if (stack->capacity == stack->max_capacity) {      // Probably will not happen.
        Foo_call* new = malloc(2 * stack->max_capacity * sizeof(Foo_call));
        CHECK_MALLOC(new);

        for (int i = 0; i < stack->capacity; i++) {
            new[i] = stack->array[i];
        }

        free(stack->array);
        stack->array = new;
        stack->max_capacity = 2 * stack->max_capacity;
    } else {
        stack->array[stack->capacity++] = f;
    }
    ASSERT_ZERO(pthread_mutex_unlock(&stack_mutex));
    ASSERT_ZERO(pthread_cond_broadcast(&stack_cond));
}