#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

#include "common/io.h"
#include "common/sumset.h"

#include <time.h>

#define MAX_STACK_SIZE 8200
#define POOL_SIZE 1000

typedef struct sharedPtr SharedPtrSumset;
struct sharedPtr {
    int refCounter;
    Sumset sumset;
    SharedPtrSumset* parent;
    SharedPtrSumset* next;
};

typedef struct {
    SharedPtrSumset* a;
    SharedPtrSumset* b;
} FooCall;

typedef struct {
    FooCall* array;
    int size;
} Stack;

// STACK FUNCTIONS.

FooCall pop(Stack* stack) {
    assert(stack->size > 0 && "Attempted to pop from an empty stack");
    return stack->array[--stack->size];
}

void push(Stack* stack, FooCall call) {
    assert(stack->size < MAX_STACK_SIZE && "Pushed to full stack");
    stack->array[stack->size++] = call;
}

Stack* initStack() {
    Stack* stack = malloc(sizeof(Stack));
    FooCall* arr = calloc(MAX_STACK_SIZE, sizeof(FooCall));
    stack->size = 0;
    stack->array = arr;

    return stack;
}

bool isEmpty(const Stack* stack) {
    return stack->size == 0;
}

// SHARED POINTER FUNCTIONS.

SharedPtrSumset* allocPtr(SharedPtrSumset** ptrPoolReady) {
    SharedPtrSumset* ptr = *ptrPoolReady;

    *ptrPoolReady = (*ptrPoolReady)->next;

    return ptr;
}

void releasePtr(SharedPtrSumset* ptr, SharedPtrSumset** ptrPoolReady) {
    while (ptr && --ptr->refCounter == 0) {
        SharedPtrSumset* tmp = ptr->parent;

        ptr->next = *ptrPoolReady;
        *ptrPoolReady = ptr;

        ptr = tmp;
    }
}

// ACTUAL SOLVING FUNCTIONS.

void swap(FooCall* f) {
    if (f->a->sumset.sum > f->b->sumset.sum) {
        SharedPtrSumset* ptr = f->a;
        f->a = f->b;
        f->b = ptr;
    }
}

static void solve(Stack* stack, InputData* input, Solution* solution) {
    SharedPtrSumset *ptrPoolReady = malloc(sizeof(SharedPtrSumset));
    SharedPtrSumset* prev = ptrPoolReady;
    for (int i = 0; i < POOL_SIZE; i++) {
        prev->next = malloc(sizeof(SharedPtrSumset));
        prev = prev->next;
        prev->next = NULL;
    }

    while(!isEmpty(stack)) {
        FooCall f = pop(stack);
        swap(&f);

        if (is_sumset_intersection_trivial(&f.a->sumset, &f.b->sumset)) {
            for (size_t i = f.a->sumset.last; i <= input->d; ++i) {
                if (!does_sumset_contain(&f.b->sumset, i)) {
                    f.a->refCounter++;
                    f.b->refCounter++;

                    FooCall call;

                    SharedPtrSumset* aWithIPtr = allocPtr(&ptrPoolReady);
                    sumset_add(&aWithIPtr->sumset, &f.a->sumset, i);

                    aWithIPtr->refCounter = 1;
                    aWithIPtr->parent = f.a;
                    call.a = aWithIPtr;
                    call.b = f.b;
                    push(stack, call);
                }
            }
        } else if ((f.a->sumset.sum == f.b->sumset.sum) &&
                   (get_sumset_intersection_size(&f.a->sumset, &f.b->sumset)) == 2) {
            if (f.b->sumset.sum > (*solution).sum) {
                solution_build(solution, input, &f.a->sumset, &f.b->sumset);
            }
        }
        releasePtr(f.a, &ptrPoolReady);
        releasePtr(f.b, &ptrPoolReady);
    }
    prev = ptrPoolReady;
    while (prev) {
        SharedPtrSumset *tmp = prev->next;
        free(prev);
        prev = tmp;
    }
}

int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    InputData input_data;
    //input_data_read(&input_data);
    input_data_init(&input_data, 8, 17, (int[]){0}, (int[]){1, 3,0});

    Solution best_solution;
    solution_init(&best_solution);

    Stack* stack = initStack();

    SharedPtrSumset *a = malloc(sizeof(SharedPtrSumset));
    SharedPtrSumset *b = malloc(sizeof(SharedPtrSumset));
    a->refCounter = 1;
    b->refCounter = 1;
    a->parent = NULL;
    b->parent = NULL;
    a->sumset = input_data.a_start;
    b->sumset = input_data.b_start;
    FooCall f;
    f.a = a;
    f.b = b;
    push(stack, f);

    solve(stack, &input_data, &best_solution);
    solution_print(&best_solution);

    free(stack->array);
    free(stack);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Execution time: %f seconds\n", time_taken);
    return 0;
}
