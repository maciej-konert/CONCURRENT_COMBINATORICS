#include <stddef.h>
#include <pthread.h>
#include <stdatomic.h>

#include "common/err.h"
#include "stack.h"
#include "shared_ptr.h"

// GLOBALS

Stack* global_stack;
pthread_mutex_t stack_mutex;
pthread_mutex_t max_mutex;
atomic_int workers_finished;

Solution best_solution;
InputData input_data;
// SOLVING FUNCTIONS

void solve(shared_ptr** ptr_pool, Stack* my_stack, Solution* curr_solution)
{
    Foo_call f = pop(my_stack);
    swap(&f);

    if (is_sumset_intersection_trivial(&f.a->sumset, &f.b->sumset)) {
        for (size_t i = f.a->sumset.last; i <= input_data.d; ++i) {
            if (!does_sumset_contain(&f.b->sumset, i)) {
                f.a->ref_count++;
                f.b->ref_count++;

                Foo_call call;
                shared_ptr* a_with_i = alloc_ptr(ptr_pool);

                sumset_add(&a_with_i->sumset, &f.a->sumset, i);

                a_with_i->ref_count = 1;
                a_with_i->parent = f.a;
                call.a = a_with_i;
                call.b = f.b;

                if (capacity(global_stack) < input_data.t && input_data.t != 1) {
                    pthread_mutex_lock(&stack_mutex);
                    push(global_stack, call);
                    pthread_mutex_unlock(&stack_mutex);
                } else {
                    push(my_stack, call);
                }
            }
        }
    } else if ((f.a->sumset.sum == f.b->sumset.sum) &&
               (get_sumset_intersection_size(&f.a->sumset, &f.b->sumset)) == 2) {
        if (f.b->sumset.sum > (*curr_solution).sum) {
            solution_build(curr_solution, &input_data, &f.a->sumset, &f.b->sumset);
        }
    }
    release_ptr(f.a, ptr_pool);
    release_ptr(f.b, ptr_pool);
}

void* worker(void* data)
{
    Solution* current_best_solution = malloc(sizeof(Solution));
    solution_init(current_best_solution);

    Stack* myStack;
    shared_ptr* ptr_pool;

    init_pool(&ptr_pool);
    init_stack(&myStack);

    while (atomic_load(&workers_finished) < input_data.t || (!is_empty(myStack) || !is_empty(global_stack))) {
        workers_finished--;

        while (!is_empty(myStack)) {
            solve(&ptr_pool, myStack, current_best_solution);
        }
        pthread_mutex_lock(&stack_mutex);
        if (!is_empty(global_stack)) {
            push(myStack, pop(global_stack));
        }
        pthread_mutex_unlock(&stack_mutex);

        workers_finished++;
    }

    pthread_mutex_lock(&max_mutex);
    if (current_best_solution->sum > best_solution.sum) {
        best_solution = *current_best_solution;
    }
    pthread_mutex_unlock(&max_mutex);

    destroy_stack(myStack);
    destroy_pool(ptr_pool);

    return NULL;
}



int main()
{
    //input_data_read(&input_data);
    input_data_init(&input_data, 3, 30, (int[]){0}, (int[]){1,0});

    solution_init(&best_solution);

    pthread_t threads[input_data.t];
    workers_finished = input_data.t;

    ASSERT_ZERO(pthread_mutex_init(&stack_mutex, NULL));
    ASSERT_ZERO(pthread_mutex_init(&max_mutex, NULL));
    init_stack(&global_stack);

    shared_ptr *a, *b;
    init_shared_ptr(&a, input_data.a_start);
    init_shared_ptr(&b, input_data.b_start);

    Foo_call f;
    f.a = a;
    f.b = b;
    push(global_stack, f);

    for (int i = 0; i < input_data.t; i++) {
        ASSERT_ZERO(pthread_create(&threads[i], NULL, worker, NULL));
    }
    for (int i = 0; i < input_data.t; i++) {
        ASSERT_ZERO(pthread_join(threads[i], NULL));
    }

    solution_print(&best_solution);
    return 0;
}
