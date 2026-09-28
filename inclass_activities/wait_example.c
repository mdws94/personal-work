#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t pid = fork();

  if (pid) {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
  }
}
