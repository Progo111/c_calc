#ifndef STACK_D_H
#define STACK_D_H

#include <stdlib.h>

#ifndef SIZE
#define SIZE 10
#endif

typedef struct stack_d {
    double *data;
    unsigned int size;
    unsigned int top;
} stack_d;

stack_d *stack_d_init();
void stack_d_destroy(stack_d **stack);
void stack_d_resize(stack_d *stack);
double pop_d(stack_d *stack);
void push_d(stack_d *stack, double value);
#endif