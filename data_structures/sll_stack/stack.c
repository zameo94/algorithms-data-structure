#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* INITIALIZATION */

sll_stack *stack_init() {
    sll_stack *stack = malloc(sizeof(*stack));

    if(stack == NULL) {
        return NULL;
    }

    SLL_list *list = initialize_list();

    if(list == NULL) {
        free(stack);
        return NULL;
    }

    stack->list = list;
    return stack;
}

/* INSERT FUNCTIONS */

int stack_push(sll_stack *stack, int data) {
    if(stack == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED; 

    return insert_head(stack->list, data);
}

/* DELETE FUNCTIONS */

int stack_pop(sll_stack *stack, int *output) {
    if(stack == NULL || stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    int status = get_head(stack->list, output);
    
    if(status != SLL_SUCCESS) return status;

    return delete_head(stack->list);
}

/* PRINTING */

void stack_print(sll_stack *stack) {
    if(stack == NULL) return;

    print_list(stack->list);
}

/* BOOLEAN CHECKS */

/* 
 * Check if the stack is empty.
 * The pointer 'stack' MUST be allocated. Passing NULL is considered 
 * a logic error and will trigger an assertion failure.
 */
bool stack_is_empty(sll_stack *stack) {
    assert(stack != NULL);

    return is_empty(stack->list);
}

/* CLEANING FUNCTIONS */

int stack_free(sll_stack **stack_ref) {
    if(stack_ref == NULL || *stack_ref == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    int result = free_list(&((*stack_ref)->list));

    if(result != SLL_SUCCESS) return result;

    free(*stack_ref);
    *stack_ref = NULL;

    return SLL_SUCCESS;
}

/* GET */

int stack_peek(sll_stack *stack, int *output) {
    if(stack == NULL || stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return get_head(stack->list, output);
}

/* SIZE */

int stack_size(sll_stack *stack) {
    if(stack == NULL || stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return length_list(stack->list);
}

/* CLEAR */

int stack_clear(sll_stack *stack) {
    if(stack == NULL || stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return clear_list(stack->list);
}

/* DUPLICATE */

int stack_duplicate(sll_stack *old_stack, sll_stack *new_stack) {
    if(old_stack == NULL || old_stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;
    if(new_stack == NULL || new_stack->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return duplicate_list(old_stack->list, new_stack->list);
}
