#define _POSIX_C_SOURCE 200809
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void my_handler(int signum) { write(STDOUT_FILENO, "CTRL-C pressed\n", 15); }

int main() {
  pid_t pid = fork();

  if (pid < 0) {
  }

  if (pid != 0) {
    // Notice that only the parent registered the handler
    struct sigaction my_act = {0};
    my_act.sa_handler = my_handler;
    my_act.sa_flags = 0;
    sigemptyset(&my_act.sa_mask);

    int ret sigaction(SIGINT, &my_act, NULL);

    if (ret == -1) {
      perror("Bad things happened");
      exit(EXIT_FAILURE);
    }

    while (1)
      sleep(1);
  } else {
    while (1) {
      sleep(2);
      printf("") kill();
    }
  }
}
