#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LOCAL_HOST "127.0.0.1"

int main() {
  printf("ClIENT:\n");

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in sockstruct;
  memset(&sockstruct, 0, sizeof(struct sockaddr_in));
  sockstruct.sin_family = AF_INET;
  sockstruct.sin_port = htons(1042);
  int ret_val = inet_pton(AF_INET, LOCAL_HOST, &sockstruct.sin_addr);
  if (ret_val == -1) {
    perror("inet_pton error");
    exit(EXIT_FAILURE);
  }

  if (connect(socket_fd, (struct sockaddr *)&sockstruct, sizeof(struct sockaddr_in)) == -1) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }
}
