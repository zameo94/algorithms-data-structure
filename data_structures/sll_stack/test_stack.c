#include "stack.h"
#include <stdio.h>

int main(void) {
    sll_stack *stack = stack_init();
    stack_push(stack, 10);
    stack_push(stack, 20);

    printf("Stack size: %d\n", stack_size(stack));
    printf("Stack:\n");
    stack_print(stack);

    sll_stack *stack2 = stack_init();
    printf("Duplication....\n");
    stack_duplicate(stack, stack2);
    printf("Stack 2:\n");
    stack_print(stack2);
    
    int val;
    stack_pop(stack, &val);
    printf("Popped: %d\n", val);

    printf("Stack size: %d\n", stack_size(stack));
    stack_print(stack);

    stack_clear(stack);
    printf("Stack size: %d\n", stack_size(stack));
    stack_print(stack);
    
    stack_free(&stack);
    stack_free(&stack2);

    return 0;
}
