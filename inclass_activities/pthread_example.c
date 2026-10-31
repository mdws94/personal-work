#define _GNU_SOURCE

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cnt = 0;

void *my_thread(void *arg) {
  // char *msg = arg;
  // printf("In thread %d: %s\n", gettid(), msg);
  // sleep(1);

  // printf("Thread done!\n");

  // return (void *)strlen(msg);
  //
  //
  return NULL;
}

int main() {
  pthread_t id1;
  pthread_t id2;
  if (pthread_create(&id1, NULL, my_thread, "Hello") != 0) {
    perror("Unable to create thread.");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&id2, NULL, my_thread, "Hello") != 0) {
    perror("Unable to create thread.");
    exit(EXIT_FAILURE);
  }

  void *thread_ret = 0;
  if (pthread_join(id1, &thread_ret) != 0) {
    perror("Unable to join");
    exit(EXIT_FAILURE);
  }

  printf("Cnt: %d", cnt);
}
