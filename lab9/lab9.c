/*
Questions to answer at top of client.c:
(You should not need to change the code in client.c)
1. What is the address of the server it is trying to connect to (IP address and port number).
   127.0.0.1 (LocalHost) and port 8000
2. Is it UDP or TCP? How do you know?
   It is TCP because the socket uses SOCK_STREAM, whereas UDP's socket uses SOCK_DGRAM
3. The client is going to send some data to the server. Where does it get this data from? How can
you tell in the code? It gets this data from STDIN_FILENO, or in otherwords standard input.
Examining the read() call tells us that.
4. How does the client program end? How can you tell that in the code?
   It ends when the file is read and closes exit(EXIT_SUCCESS) and the precedinging line is how we
can tell that behaviour from the code. It can also fail early with exit(EXIT_FAILURE)
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUF_SIZE 64
#define ADDR "127.0.0.1"

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

int main() {
  struct sockaddr_in addr;
  int sfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, ADDR, &addr.sin_addr) <= 0) {
    handle_error("inet_pton");
  }

  int res = connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (res == -1) {
    handle_error("connect");
  }

  while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 1) {
    if (write(sfd, buf, num_read) != num_read) {
      handle_error("write");
    }
    printf("Just sent %zd bytes.\n", num_read);
  }

  if (num_read == -1) {
    handle_error("read");
  }

  close(sfd);
  exit(EXIT_SUCCESS);
}
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 64
#define PORT 8000
#define LISTEN_BACKLOG 32

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

// Shared counters for: total # messages, and counter of clients (used for
// assigning client IDs)
int total_message_count = 0;
int client_id_counter = 1;

// Mutexs to protect above global state.
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_id_mutex = PTHREAD_MUTEX_INITIALIZER;

struct client_info {
  int cfd;
  int client_id;
};

void *handle_client(void *arg) {
  struct client_info *client = (struct client_info *)arg;

  ssize_t num_read;
  char buff[BUF_SIZE];
  while ((num_read = read(client->cfd, buff, BUF_SIZE - 1)) > 0) {
    buff[num_read] = '\0';

    int msg_no;
    pthread_mutex_lock(&count_mutex);
    msg_no = ++total_message_count;
    pthread_mutex_unlock(&count_mutex);

    printf("MESSAGE NO: %d, CLIENT ID: %d, MESSAGE: %s", msg_no, client->client_id, buff);
  }

  if (num_read == -1) {
    perror("Read error");

  } else {
    // num_read is 0
    printf("Closing thread for client: %d\n", client->client_id);
  }

  if (close(client->cfd) == -1) {
    perror("Socket close error");
  }
  free(client);

  return NULL;
}

int main() {
  struct sockaddr_in addr;
  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
    handle_error("bind");
  }

  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    handle_error("listen");
  }

  for (;;) {
    int cfd = accept(sfd, NULL, NULL);
    if (cfd == -1) {
      handle_error("accept");
    }

    struct client_info *c_info = malloc(sizeof(struct client_info));
    if (!c_info) {
      handle_error("malloc");
    }

    c_info->cfd = cfd;

    pthread_mutex_lock(&client_id_mutex);
    c_info->client_id = client_id_counter;
    printf("Client created:\tCLIENT ID: %d, SOCKET FD: %d\n", c_info->client_id, c_info->cfd);
    client_id_counter++;
    pthread_mutex_unlock(&client_id_mutex);

    pthread_t thread;
    int pthrd_ret = pthread_create(&thread, NULL, handle_client, c_info);
    if (pthrd_ret) {
      fprintf(stderr, "THREAD ACCEPT ERROR:\tERRNO: %d; %s\n", pthrd_ret, strerror(pthrd_ret));
      exit(EXIT_FAILURE);
    }

    pthrd_ret = pthread_detach(thread);
    if (pthrd_ret) {
      fprintf(stderr, "THREAD DETACH ERROR:\tERRNO: %d; %s\n", pthrd_ret, strerror(pthrd_ret));
      exit(EXIT_FAILURE);
    }
  }

  if (close(sfd) == -1) {
    handle_error("close");
  }

  return 0;
}
