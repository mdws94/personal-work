<<<<<<< HEAD
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
=======
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *buff = NULL;
  size_t size = 0;

  while (true) {
    printf("Enter a program path to run:\n> ");

    ssize_t length = 0;
    if ((length = getline(&buff, &size, stdin)) != -1) {
      if (length > 0 && buff[length - 1] == '\n') {
        buff[length - 1] = '\0'; // Set the last char to null terminator, necessary.
      }

      pid_t pid;
      if (!(pid = fork())) {
        // Child
        if (execlp(buff, buff, NULL)) {
          printf("Error executing program\n");
          break;
        }
      } else if (pid < 0) {
        // Failure
        printf("Fork failure\n");
        break;
      } else {
        // Parent
        int status = 0;

        if (waitpid(pid, &status, 0) == -1) {
          printf("Wait failed\n");
          exit(EXIT_FAILURE);
        }
      }
    } else {
      printf("Getline failure\n");
      break;
    }
  }

  free(buff);

  return 0;
>>>>>>> origin/main
}
