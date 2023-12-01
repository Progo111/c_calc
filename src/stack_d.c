#include "stack_d.h"

// stack для double
stack_d *stack_d_init() {
    stack_d *new_stack = malloc(sizeof(stack_d));
    new_stack->data = malloc(SIZE * sizeof(double));
    new_stack->size = SIZE;
    new_stack->top = 0;
    return new_stack;
}

void stack_d_destroy(stack_d **stack) {
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

void stack_d_resize(stack_d *stack) {
    stack->size *= 2;
    stack->data = realloc(stack->data, stack->size * sizeof(double));
}

double pop_d(stack_d *stack) {
    double res = 0;
    if (stack->top > 0) {
        stack->top--;
        res = stack->data[stack->top];
    }
    return res;
}

void push_d(stack_d *stack, double value) {
    if (stack->top >= stack->size) {
        stack_d_resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}