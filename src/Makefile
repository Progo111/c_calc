CC=gcc -Wall -Werror -Wextra -std=c11

all: graph.c graph_func.c stack.c stack_d.c
	$(CC) graph.c graph_func.c stack.c stack_d.c -lm -o ../build/graph

run: clean all
	./../build/graph

check: cppcheck clang

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clang:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

clean: 
	rm -rf *.o ../build/graph