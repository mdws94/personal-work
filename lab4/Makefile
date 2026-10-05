all: lab4

lab4: lab4.c
	clang -fsanitize=address -Wall -Werror -g -o lab4 lab4.c

.PHONY: clean
clean:
	rm -f lab4
