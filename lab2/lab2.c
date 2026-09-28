#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pid_t fork(void);

int main() {
  printf("Enter programs to run: \n");

  char *buff;
  size_t size = 0;

  if (getline(&buff, &size, stdin) != -1L) {

  } else {
    printf("Getline Error")
  }

  free(buff);
}
