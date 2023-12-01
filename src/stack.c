#include "stack.h"

// stack для char
stack_c *stack_init() {
    stack_c *new_stack = malloc(sizeof(stack_c));
    new_stack->data = malloc(SIZE * sizeof(char));
    new_stack->size = SIZE;
    new_stack->top = 0;
    return new_stack;
}

void stack_destroy(stack_c **stack) {
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

void stack_resize(stack_c *stack) {
    stack->size *= 2;
    stack->data = realloc(stack->data, stack->size * sizeof(char));
}

int pop(stack_c *stack) {
    int res = ' ';
    if (stack->top > 0) {
        stack->top--;
        res = stack->data[stack->top];
    }
    return res;
}

int peek(stack_c *stack) {
    int res = ' ';
    if (stack->top > 0) {
        res = stack->data[stack->top - 1];
    }
    return res;
}

void push(stack_c *stack, char value) {
    if (stack->top >= stack->size) {
        stack_resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}