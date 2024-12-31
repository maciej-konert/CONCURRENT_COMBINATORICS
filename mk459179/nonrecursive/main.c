#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/io.h"
#include "common/sumset.h"

InputData input_data;
Solution best_solution;

typedef struct solveSet solveSet;
struct solveSet {
    const Sumset *a;
    const Sumset *b;
    solveSet *previous;
};

void push(solveSet** top, const Sumset* aS, const Sumset* bS) {
    solveSet* prevTop = *top;

    solveSet* newTop = malloc(sizeof(struct solveSet));
    if (!newTop) {
        exit(1);
    }
    newTop->a = aS;
    newTop->b = bS;
    if (aS->sum > bS->sum) {
        newTop->a = bS;
        newTop->b = aS;
    }
    newTop->previous = prevTop;

    *top = newTop;
}

solveSet* pop(solveSet** top) {
    if (*top != NULL) {
        solveSet *topSet = *top;
        *top = topSet->previous;

        return topSet;
    } else {
        return NULL;
    }
}

void freeStack(solveSet** top) {
    solveSet* topSet = *top;
    while (topSet != NULL) {
        solveSet* toFree = topSet;
        topSet = topSet->previous;
        free(toFree);
    }
    *top = NULL;
}

typedef struct toFreeNode toFreeNode;
struct toFreeNode {
    Sumset* set;
    toFreeNode* prev;
};

void pushToFree(toFreeNode** top, Sumset* setToFree) {
    toFreeNode* newNode = malloc(sizeof(struct toFreeNode));
    newNode->prev = *top;
    newNode->set = setToFree;

    *top = newNode;
}

void freeNodes(toFreeNode** top) {
    toFreeNode* newTop = *top;
    while (newTop != NULL) {
        toFreeNode* toF = newTop;
        newTop = newTop->prev;
        free(toF->set);
        free(toF);
    }
    *top = NULL;
}

void solve(const Sumset* aStart, const Sumset* bStart) {
    solveSet* top = NULL;
    push(&top, aStart, bStart);
    toFreeNode* topF = NULL;

    while (top != NULL) {
        solveSet* currentSet = pop(&top);
        const Sumset* a = currentSet->a;
        const Sumset* b = currentSet->b;
        free(currentSet);

        if (is_sumset_intersection_trivial(a, b)) { // s(a) ∩ s(b) = {0}.
            for (size_t i = a->last; i <= input_data.d; ++i) {
                if (!does_sumset_contain(b, i)) {
                    Sumset* a_with_i = malloc(sizeof(Sumset));
                    if (!a_with_i) {
                        exit(1);
                    }

                    sumset_add(a_with_i, a, i);

                    push(&top, a_with_i, b);
                    pushToFree(&topF, a_with_i);
                }
            }
        } else if ((a->sum == b->sum) && (get_sumset_intersection_size(a, b) == 2)) { // s(a) ∩ s(b) = {0, ∑b}.
            if (b->sum > best_solution.sum)
                solution_build(&best_solution, &input_data, a, b);
        }
    }
    freeStack(&top);
    freeNodes(&topF);

}

int main()
{
    input_data_read(&input_data);
    //input_data_init(&input_data, 8, 10, (int[]){0}, (int[]){1, 0});

    solution_init(&best_solution);

    solve(&input_data.a_start, &input_data.b_start);

    // ...

    solution_print(&best_solution);
    return 0;
}