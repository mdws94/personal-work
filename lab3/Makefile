all: lab3

lab3: lab3.c
	clang -fsanitize=address -Wall -Werror -g -o lab3 lab3.c

.PHONY: clean
clean:
	rm -f lab3
