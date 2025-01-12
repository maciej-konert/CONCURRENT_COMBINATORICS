#include <pthread.h>

#include "common/err.h"
#include "stack.h"
#include "shared_ptr.h"
#include <stdio.h>
// GLOBALS

Stack* global_stack;
pthread_mutex_t stack_mutex;
pthread_mutex_t max_mutex;
int workers_finished = 0;
bool running = true;
pthread_cond_t stack_cond;

Solution best_solution;
InputData input_data;

atomic_int count_debug = 0;
// SOLVING FUNCTIONS

static void solveRecursively(const Sumset* a, const Sumset* b, Solution* curr_best_solution)
{
    if (a->sum > b->sum)
        return solveRecursively(b, a, curr_best_solution);

    if (is_sumset_intersection_trivial(a, b)) { // s(a) ∩ s(b) = {0}.
        for (size_t i = a->last; i <= input_data.d; ++i) {
            if (!does_sumset_contain(b, i)) {
                Sumset a_with_i;
                sumset_add(&a_with_i, a, i);
                solveRecursively(&a_with_i, b, curr_best_solution);
            }
        }
    } else if ((a->sum == b->sum) && (get_sumset_intersection_size(a, b) == 2)) { // s(a) ∩ s(b) = {0, ∑b}.
        if (b->sum > best_solution.sum) {
            solution_build(&best_solution, &input_data, a, b);
        }
    }
    count_debug++;
}

void solve(shared_ptr** ptr_pool, Stack* my_stack, Solution* curr_solution)
{
    Foo_call f = pop(my_stack);
    swap(&f);

    if (is_sumset_intersection_trivial(&f.a->sumset, &f.b->sumset)) {
        bool first = true;
        bool push_to_stack = false;
        if (capacity(global_stack) < 2 * input_data.t)
            push_to_stack = true;

        Foo_call first_call;
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

                if (first) {
                    first_call = call;
                    first = false;
                } else if (push_to_stack){
                    pthread_mutex_lock(&stack_mutex);
                    push(global_stack, call);
                    pthread_mutex_unlock(&stack_mutex);
                    pthread_cond_broadcast(&stack_cond);
                } else {
                    solveRecursively(&call.a->sumset, &call.b->sumset, curr_solution);
                    release_ptr(call.a, ptr_pool);
                    release_ptr(call.b, ptr_pool);
                }
            }
        }
        if (!first) {
            solveRecursively(&first_call.a->sumset, &first_call.b->sumset, curr_solution);
            release_ptr(first_call.a, ptr_pool);
            release_ptr(first_call.b, ptr_pool);
        }
    } else if ((f.a->sumset.sum == f.b->sumset.sum) &&
               (get_sumset_intersection_size(&f.a->sumset, &f.b->sumset)) == 2) {
        if (f.b->sumset.sum > (*curr_solution).sum) {
            solution_build(curr_solution, &input_data, &f.a->sumset, &f.b->sumset);
        }
    }
    count_debug++;
    release_ptr(f.a, ptr_pool);
    release_ptr(f.b, ptr_pool);
}

void* worker(void* data)
{
    Solution current_best_solution;
    solution_init(&current_best_solution);

    Stack* my_stack;
    shared_ptr* ptr_pool;

    init_stack(&my_stack);
    init_pool(&ptr_pool);

    if (input_data.t == 1) {
        Foo_call f = pop(global_stack);
        solveRecursively(&f.a->sumset, &f.b->sumset, &current_best_solution);
        release_ptr(f.a, &ptr_pool);
        release_ptr(f.b, &ptr_pool);
    } else {
        while (running) {
            if (!is_empty(my_stack)) {
                solve(&ptr_pool, my_stack, &current_best_solution);
            }

            pthread_mutex_lock(&stack_mutex);
            workers_finished++;

            if (workers_finished == input_data.t) {
                running = false;
            } else {
                while (running && is_empty(global_stack)) {
                    pthread_cond_wait(&stack_cond, &stack_mutex);
                }
            }
            if (running) {
                push(my_stack, pop(global_stack));
            }
            workers_finished--;
            pthread_mutex_unlock(&stack_mutex);
        }
    }
    pthread_cond_broadcast(&stack_cond);

    pthread_mutex_lock(&max_mutex);
    if ((&current_best_solution)->sum > best_solution.sum) {
        best_solution = current_best_solution;
    }
    pthread_mutex_unlock(&max_mutex);

    destroy_stack(my_stack);
    destroy_pool(ptr_pool);

    return NULL;
}



int main()
{
    //input_data_read(&input_data);
//    input_data_init(&input_data, 2, 10, (int[]){1, 0}, (int[]){4,0});    // NIE DIZALA
    input_data_init(&input_data, 2, 34, (int[]){0}, (int[]){1, 0});

    solution_init(&best_solution);

    pthread_t threads[input_data.t];

    ASSERT_ZERO(pthread_mutex_init(&stack_mutex, NULL));
    ASSERT_ZERO(pthread_mutex_init(&max_mutex, NULL));
    ASSERT_ZERO(pthread_cond_init(&stack_cond, NULL));
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
    destroy_stack(global_stack);
    pthread_mutex_destroy(&stack_mutex);

    solution_print(&best_solution);
    printf("states: %d\n", count_debug);
    return 0;
}
