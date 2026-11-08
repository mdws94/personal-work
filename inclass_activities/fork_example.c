#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("Start PID=%d. parent PID=%d\n", getpid());
  pid_t pid = fork();

  if (pid == 0) {
    printf("CHILD: PID=%d, parent PID=%d\n", getpid(), getppid());
  }

  printf("CHILD: PID=%d, parent PID=%d\n", pid, getpid());

  return 0;
}
