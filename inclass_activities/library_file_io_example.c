#include <stdio.h>
#include <unistd.h>

int main() {
  char *str = "Hello World!\n";

  FILE *f = fopen("tmp", "w+");

  fprintf(f, "%s", str);
  fflush(f); // Need to flush buffered IO
  while (1) {
    sleep(30);
  }
}
