#ifndef STACK_H
#define STACK_H

#include "../singly_linked_list/sll.h"
#include <stdbool.h>

typedef struct {
    SLL_list *list;
} sll_stack;

/* PROTOTYPES FUNCTIONS */

sll_stack *stack_init();

// Insert
int stack_push(sll_stack *stack, int data);

// Delete
int stack_pop(sll_stack *stack, int *output);

// Get
int stack_peek(sll_stack *stack, int *output);

// Utility
void stack_print(sll_stack *stack);
int stack_free(sll_stack **stack_ref);
bool stack_is_empty(sll_stack *stack);
int stack_size(sll_stack *stack);
int stack_clear(sll_stack *stack);
int stack_duplicate(sll_stack *old_stack, sll_stack *new_stack);

#endif
