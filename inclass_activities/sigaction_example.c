#define _POSIX_C_SOURCE 200809
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

void my_handler(int signum) { write(STDOUT_FILENO, "CTRL-C pressed\n", 15); }

int main() {

  struct sigaction my_act = {0};
  my_act.sa_handler = my_handler;
  my_act.sa_flags = 0;
  sigemptyset(&my_act.sa_mask);

  sigaction(SIGINT, &my_act, NULL);

  while (1)
    sleep(1);
}
