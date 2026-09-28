#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      add_to_history(input);
    } else {
      print_history();
    }
  }
}

char *get_input() {
  char *buff = NULL;
  size_t size = 0;
  ssize_t length = 0;

  printf("Enter input:\n> ");

  if ((length = getline(&buff, &size, stdin)) != -1) {
    buff[length - 1] = '\0';
    return buff;
  } else {
    printf("Getline failure");
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
    printf("Error removing oldest record");
  }
}
void print_history() {
  if (!history_count) {
    for (int i = 0; i <= history_count; i++) {
      printf("%s\n", input_history[i]);
    }
  } else {
    printf("Input history empty");
  }
}
