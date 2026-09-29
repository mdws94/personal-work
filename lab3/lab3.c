#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LENGTH 5

char *input_history[MAX_LENGTH];
int history_count = 0;

void add_to_history(char *input);
void remove_oldest_record();
void print_history();
char *get_input();

int main() {
  while (true) {
    char *input = get_input();

    if (!strcmp(input, "print")) {
      print_history();
    } else {
      add_to_history(input);
    }
  }

  while (history_count) {
    free(input_history[history_count]);
  }
}

char *get_input() {
  char *buff = NULL;
  size_t size = 0;
  ssize_t length = 0;

  printf("Enter input (input 'print' to print history):\n> ");

  if ((length = getline(&buff, &size, stdin)) != -1) {
    if (size > 0 && buff[length - 1] == '\n') {
      buff[length - 1] = '\0';
    }
    return buff;
  } else {
    perror("Getline failure\n");
    exit(1);
  }
}

void add_to_history(char *input) {
  if (history_count < 5) {
    input_history[history_count] = input;
    history_count++;
  } else {
    remove_oldest_record();
    input_history[history_count] = input;
    history_count++;
  }
}

void remove_oldest_record() {
  if (history_count > 0) {
    free(input_history[0]);

    for (int i = 1; i <= history_count; i++) {
      input_history[i - 1] = input_history[i];
    }

    history_count--;

  } else {
    perror("Error removing oldest record");
  }
}
void print_history() {
  if (history_count > 0) {
    for (int i = 0; i <= history_count; i++) {
      if (input_history[i]) {
        printf("%s\n", input_history[i]);
      }
    }
  } else {
    printf("Input history empty\n");
  }
}
