#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#ifndef SIZE
#define SIZE 10
#endif

typedef struct stack_c {
    char *data;
    unsigned int size;
    unsigned int top;
} stack_c;

stack_c *stack_init();
void stack_destroy(stack_c **stack);
void stack_resize(stack_c *stack);
int pop(stack_c *stack);
int peek(stack_c *stack);
void push(stack_c *stack, char value);
#endif