#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Please input a message:\n> ");

  char *buff = NULL;
  size_t size = 0;

  if (getline(&buff, &size, stdin) != -1L) {
    char *input_str = buff;
    char *delim = " \t\n\r";
    char *token = NULL;
    char *save_ptr = NULL;

    while ((token = strtok_r(input_str, delim, &save_ptr))) {
      printf("Token: '%s'\n", token);

      input_str = NULL;
    }
  } else {
    printf("Getline failure\n");
  }
  free(buff);
}
