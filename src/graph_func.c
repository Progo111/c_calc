#include "graph.h"

// Реализация функций
void operator_priority(int *arr) {
    arr[' '] = -1;
    arr['+'] = 0;
    arr['-'] = 0;
    arr['*'] = 1;
    arr['/'] = 1;
    arr['s'] = 2;
    arr['c'] = 2;
    arr['t'] = 2;
    arr['g'] = 2;
    arr['q'] = 2;
    arr['l'] = 2;
    arr['~'] = 4;
    arr['('] = 5;
    arr[')'] = 5;
}

// польская нотация
char *poland_natation(char *string) {
    stack_c *operators = stack_init();
    char *result = malloc(2 * strlen(string) * sizeof(char));
    int priority[256];
    operator_priority(priority);
    int index = 0;
    int i = 0;
    while (i < (int)strlen(string)) {
        if ((string[i] >= '0' && string[i] <= '9') || string[i] == 'x' || string[i] == '.') {
            result[index++] = string[i];
        } else if (strchr("+-*/sctgql~()", string[i]) != NULL) {
            result[index++] = ' ';
            if (operators->top == 0 || priority[peek(operators)] < priority[(int)string[i]] ||
                peek(operators) == '(') {
                push(operators, string[i]);
            } else if (priority[peek(operators)] >= priority[(int)string[i]]) {
                while (priority[peek(operators)] >= priority[(int)string[i]] && peek(operators) != '(') {
                    if (peek(operators) == ')') {
                        pop(operators);
                        while (peek(operators) != '(') {
                            result[index++] = pop(operators);
                        }
                        pop(operators);
                    } else {
                        //                        while (priority[peek(operators)] >= priority[(int)
                        //                        string[i]] && peek(operators) != '(') {
                        result[index++] = pop(operators);
                        //                        }
                    }
                }
                push(operators, string[i]);
            }
        }
        ++i;
    }
    while (operators->top > 0) {
        if (priority[peek(operators)] == 5) {
            pop(operators);
        } else {
            result[index++] = pop(operators);
        }
    }
    stack_destroy(&operators);
    return result;
}

char *input() {
    char *string = malloc(sizeof(char) * SIZE);
    int i = 0;
    int size = SIZE;
    int ch = getchar();
    while (ch != '\n') {
        if (size <= i) {
            size += SIZE;
            char *ptr = realloc(string, size);
            if (ptr == NULL) {
                free(ptr);
            } else {
                string = ptr;
            }
        }
        string[i++] = ch;
        ch = getchar();
    }
    return string;
}

void change_symbol(char *string) {
    char *ptr;
    while (strstr(string, "sin") != NULL) {
        ptr = strstr(string, "sin");
        *(ptr + 1) = ' ';
        *(ptr + 2) = ' ';
    }
    while (strstr(string, "cos") != NULL) {
        ptr = strstr(string, "cos");
        *(ptr + 1) = ' ';
        *(ptr + 2) = ' ';
    }
    while (strstr(string, "tan") != NULL) {
        ptr = strstr(string, "tan");
        *(ptr + 1) = ' ';
        *(ptr + 2) = ' ';
    }
    while (strstr(string, "ctg") != NULL) {
        ptr = strstr(string, "ctg");
        *(ptr + 1) = ' ';
        *(ptr + 2) = ' ';
        *ptr = 'g';
    }
    while (strstr(string, "ln") != NULL) {
        ptr = strstr(string, "ln");
        *(ptr + 1) = ' ';
    }
    while (strstr(string, "sqrt") != NULL) {
        ptr = strstr(string, "sqrt");
        *(ptr + 1) = ' ';
        *(ptr + 2) = ' ';
        *(ptr + 3) = ' ';
        *ptr = 'q';
    }
    while (strstr(string, "(-") != NULL) {
        ptr = strstr(string, "(-");
        *(ptr + 1) = '~';
    }
    if (string[0] == '-') {
        string[0] = '~';
    }
}

double calculate_help(char **ptr) {
    double result = 0.0;
    int flag = 0;
    int i = -1;
    while ((**ptr >= '0' && **ptr <= '9') || **ptr == '.') {
        if (**ptr == '.') {
            flag = 1;
            ++(*ptr);
            continue;
        }
        if (flag == 0) {
            result = result * 10 + ((int)(**ptr) % 48);
            ++(*ptr);
        } else {
            result = result + pow(10, i--) * ((double)((int)(**ptr) % 48));
            ++(*ptr);
        }
    }
    return result;
}

double calculate(char *string, double x) {
    stack_d *nums = stack_d_init();
    char *ptr = string;
    while (ptr - string < (long int)strlen(string)) {
        if (*ptr >= '0' && *ptr <= '9') {
            push_d(nums, calculate_help(&ptr));
        } else if (strchr("+-*/", *ptr) != NULL) {
            if (nums->top < 2) {
                printf("fail");
                break;
            }
            double arg2 = pop_d(nums);
            double arg1 = pop_d(nums);
            switch (*ptr) {
                case '+':
                    push_d(nums, arg1 + arg2);
                    break;
                case '-':
                    push_d(nums, arg1 - arg2);
                    break;
                case '*':
                    push_d(nums, arg1 * arg2);
                    break;
                case '/':
                    if (arg2 <= 1E-7) {
                        printf("fail");
                        break;
                    }
                    push_d(nums, arg1 / arg2);
                    break;
                default:
                    break;
            }
            ptr++;
        } else if (strchr("sctgql~", *ptr) != NULL) {
            if (nums->top < 1) {
                printf("fail");
                break;
            }
            double arg1 = pop_d(nums);
            switch (*ptr) {
                case 's':
                    push_d(nums, sin(arg1));
                    break;
                case 'c':
                    push_d(nums, cos(arg1));
                    break;
                case 't':
                    push_d(nums, tan(arg1));
                    break;
                case 'g':
                    push_d(nums, 1.0 / tan(arg1));
                    break;
                case 'q':
                    push_d(nums, sqrt(arg1));
                    break;
                case 'l':
                    push_d(nums, log(arg1));
                    break;
                case '~':
                    push_d(nums, 0 - arg1);
                    break;
            }
            ++ptr;
        } else if (*ptr == 'x') {
            push_d(nums, x);
            ++ptr;
        } else {
            ++ptr;
        }
    }
    if (nums->top != 1) {
        printf("fail");
    }
    double result = pop_d(nums);
    stack_d_destroy(&nums);
    return result;
}

void graph(char **matrix, char *string) {
    double y[25];
    double step_y = 2.0 / (HEIGHT - 1);
    for (int i = 0; i < HEIGHT; ++i) {
        y[i] = -1 + step_y * i;
    }
    double x[80];
    double step_x = (4 * PI) / (WIDTH - 1);
    for (int i = 0; i < WIDTH; ++i) {
        x[i] = 0.0 + step_x * i;
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            matrix[i][j] = NO_GRAPH;
        }
    }

    for (int i = 0; i < WIDTH; ++i) {
        double value = calculate(string, x[i]);
        double min = fabs(y[0] - value);
        if (fabs(value) - 1 > 1E-7) {
            continue;
        }
        int min_index = 0;
        for (int j = 0; j < HEIGHT; ++j) {
            if (min > fabs(y[j] - value)) {
                min_index = j;
                min = fabs(y[j] - value);
            }
        }
        matrix[min_index][i] = GRAPH;
    }
}

void output(char **matrix) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", matrix[i][j]);
        }
        if (i < HEIGHT - 1) {
            printf("\n");
        }
    }
}
