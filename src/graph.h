#ifndef GRAPH_H
#define GRAPH_H

// Используемые библеотеки
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "stack_d.h"
// Используемые константы
#define PI 3.14159265358979323846
#define WIDTH 80
#define HEIGHT 25
#define GRAPH '*'
#define NO_GRAPH '.'
#ifndef SIZE
#define SIZE 10
#endif
// Используемые структуры

// Определение Функций
void operator_priority(int *arr);

char *input();

void change_symbol(char *);

char *poland_natation(char *);

double calculate(char *, double);

double calculate_help(char **);

void graph(char **, char *);

void output(char **);

#endif  // GRAPH_H