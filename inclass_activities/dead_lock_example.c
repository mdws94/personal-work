#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex_0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;

static void *thread0(void *arg) {
  pthread_mutex_lock(&mutex_0);
  printf("thread0: muegettid());
  pthread_mutex_lock(&mutex_0);
  pthread_mutex_unlock(&mutex_1);
  sleep(1);
  pthread_exit(0);
}

int main() {
  int i = 1;
  while (1) {
    pthread_t t1, t2;
    printf("Ran %d times.\n", i);
    pthread_create(&t1, NULL, func, NULL);
    pthread_create(&t2, NULL, func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    i++;
  }
  return 0;
}
