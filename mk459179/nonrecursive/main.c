#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

#include "common/io.h"
#include "common/sumset.h"

#include <time.h>

#define MAX_STACK_SIZE 8200

int x =0;
int y = 0;

typedef struct sharedPtr SharedPtrSumset;
struct sharedPtr {
    int refCounter;
    Sumset  sumset;
    SharedPtrSumset* parent;
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

bool isEmpty(Stack* stack) {
    return stack->size == 0;
}

// SHARED POINTER FUNCTIONS.

void releasePtr(SharedPtrSumset* ptr) {
    if (ptr->refCounter == 1) {
        free(ptr);
        y++;
    } else {
        ptr->refCounter--;
    }
}

// ACTUAL SOLVING FUNCTIONS.

void incrementParent(SharedPtrSumset* ptr) {
    SharedPtrSumset* currPtr = ptr->parent;

    while (currPtr) {
        currPtr->refCounter++;
        currPtr = currPtr->parent;
    }
}

void decrementParent(SharedPtrSumset* ptr) {
    SharedPtrSumset* currPtr = ptr->parent;

    while (currPtr) {
        SharedPtrSumset* p = currPtr->parent;
        releasePtr(currPtr);
        currPtr = p;
    }
}

void swap(FooCall* f) {
    if ((*f).a->sumset.sum > (*f).b->sumset.sum) {
        SharedPtrSumset* ptr = (*f).a;
        (*f).a = (*f).b;
        (*f).b = ptr;
    }
}

static void solve(Stack* stack, InputData* input, Solution* solution) {

    while(!isEmpty(stack)) {
        FooCall f = pop(stack);
        swap(&f);

        if (is_sumset_intersection_trivial(&f.a->sumset, &f.b->sumset)) {
            for (size_t i = f.a->sumset.last; i <= input->d; ++i) {
                if (!does_sumset_contain(&f.b->sumset, i)) {
                    f.a->refCounter++;
                    f.b->refCounter++;

                    FooCall call;
                    Sumset* a_with_i = malloc(sizeof(Sumset));
                    sumset_add(a_with_i, &f.a->sumset, i);
                    SharedPtrSumset* aWithIPtr = malloc(sizeof(SharedPtrSumset));

                    aWithIPtr->sumset = *a_with_i;
                    aWithIPtr->refCounter = 1;
                    aWithIPtr->parent = f.a;
                    x++;
                    call.a = aWithIPtr;
                    call.b = f.b;
                    push(stack, call);
                    incrementParent(f.a);
                    incrementParent(f.b);
                }
            }
        } else if ((f.a->sumset.sum == f.b->sumset.sum) &&
                (get_sumset_intersection_size(&f.a->sumset, &f.b->sumset)) == 2) {
            if (f.b->sumset.sum > (*solution).sum) {
                solution_build(solution, input, &f.a->sumset, &f.b->sumset);
            }
        }
        decrementParent(f.a);
        decrementParent(f.b);
        releasePtr(f.a);
        releasePtr(f.b);
    }
}

int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    InputData input_data;
    //input_data_read(&input_data);
    input_data_init(&input_data, 8, 10, (int[]){0}, (int[]){1, 0});

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

    printf("%d %d", x, y);
    return 0;
}