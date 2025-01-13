#include <pthread.h>

#include "common/err.h"
#include "stack.h"
#include "shared_ptr.h"
#include <stdio.h>
// GLOBALS

Stack* global_stack;
pthread_mutex_t max_mutex;

static Solution best_solution;
static InputData input_data;

// SOLVING FUNCTIONS
static void solve_recursive(Sumset* a, Sumset* b, Solution* curr_best_solution)
{
    if (a->sum > b->sum)
        return solve_recursive(b, a, curr_best_solution);

    if (is_sumset_intersection_trivial(a, b)) { // s(a) ∩ s(b) = {0}.
        for (size_t i = a->last; i <= input_data.d; ++i) {
            if (!does_sumset_contain(b, i)) {
                Sumset a_with_i;
                sumset_add(&a_with_i, a, i);
                solve_recursive(&a_with_i, b, curr_best_solution);
            }
        }
    } else if ((a->sum == b->sum) && (get_sumset_intersection_size(a, b) == 2)) { // s(a) ∩ s(b) = {0, ∑b}.
        if (b->sum > curr_best_solution->sum) {
            solution_build(curr_best_solution, &input_data, a, b);
        }
    }
}

void solve_iter(shared_ptr* a_ptr,shared_ptr * b_ptr, shared_ptr** ptr_pool, Solution* curr_best_solution) {
    if (a_ptr->sumset.sum > b_ptr->sumset.sum) {
        return solve_iter(b_ptr, a_ptr, ptr_pool, curr_best_solution);
    }

    if (is_sumset_intersection_trivial(&a_ptr->sumset, &b_ptr->sumset)) {
        bool first = true;
        Sumset a_with_i;
        for (size_t i = a_ptr->sumset.last; i <= input_data.d; ++i) {
            if (!does_sumset_contain(&b_ptr->sumset, i)) {
                a_ptr->ref_count++;
                b_ptr->ref_count++;

                if (first) {
                    sumset_add(&a_with_i, &a_ptr->sumset, i);
                    first = false;
                } else {
                    shared_ptr *a_with_i_ptr = alloc_ptr(ptr_pool);
                    sumset_add(&a_with_i_ptr->sumset, &a_ptr->sumset, i);

                    a_with_i_ptr->ref_count = 1;
                    a_with_i_ptr->parent = a_ptr;
                    Foo_call f;
                    f.a = a_with_i_ptr;
                    f.b = b_ptr;
                    push(global_stack, f);
                }
            }
        }
        if (!first) {
            solve_recursive(&a_with_i, &b_ptr->sumset, curr_best_solution);
            release_ptr(a_ptr, ptr_pool);
            release_ptr(b_ptr, ptr_pool);
        }
    } else if ((a_ptr->sumset.sum == b_ptr->sumset.sum) && get_sumset_intersection_size(&a_ptr->sumset, &b_ptr->sumset) == 2) {
        if (b_ptr->sumset.sum > curr_best_solution->sum) {
            solution_build(curr_best_solution, &input_data, &a_ptr->sumset, &b_ptr->sumset);
        }
    }
}

void* worker(void* data)
{
    Foo_call f;
    shared_ptr* ptr_pool;
    Solution curr_best_solution;

    solution_init(&curr_best_solution);
    init_pool(&ptr_pool);

    while (true) {
        if (!pop(global_stack, &f)) {
            break;
        }
        if (global_stack->capacity < 2 * input_data.t) {
            solve_iter(f.a, f.b, &ptr_pool, &curr_best_solution);
        } else {
            solve_recursive(&f.a->sumset, &f.b->sumset, &curr_best_solution);
        }

        release_ptr(f.a, &ptr_pool);
        release_ptr(f.b, &ptr_pool);
    }
    ASSERT_ZERO(pthread_cond_broadcast(&stack_cond));

    ASSERT_ZERO(pthread_mutex_lock(&max_mutex));
    if ((&curr_best_solution)->sum > best_solution.sum) {
        best_solution = curr_best_solution;
    }
    ASSERT_ZERO(pthread_mutex_unlock(&max_mutex));
    destroy_pool(ptr_pool);

    return NULL;
}



int main()
{
    input_data_read(&input_data);

    solution_init(&best_solution);

    pthread_t threads[input_data.t];

    ASSERT_ZERO(pthread_mutex_init(&max_mutex, NULL));
    init_stack(&global_stack, input_data.t);

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
    destroy_stack(global_stack);
    pthread_mutex_destroy(&max_mutex);

    solution_print(&best_solution);
    return 0;
}
