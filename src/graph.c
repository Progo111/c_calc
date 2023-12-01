#include "graph.h"

// Основная программа
int main() {
    printf("Ввод: ");
    char *input_str = input();
    change_symbol(input_str);
    char *str = poland_natation(input_str);
    char **matrix = malloc(HEIGHT * sizeof(char *) + HEIGHT * WIDTH * sizeof(char));
    for (int i = 0; i < HEIGHT; ++i) {
        matrix[i] = (char *)(matrix + HEIGHT) + i * WIDTH;
    }
    graph(matrix, str);
    output(matrix);
    free(str);
    free(input_str);
    free(matrix);
    return 0;
}