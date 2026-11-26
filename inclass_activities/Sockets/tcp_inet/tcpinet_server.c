#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  printf("SERVER:\n");

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in sockstruct;
  memset(&sockstruct, 0, sizeof(struct sockaddr_in));
  sockstruct.sin_family = AF_INET;
  sockstruct.sin_port = htonl(1042);
  sockstruct.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socket_fd, (struct sockaddr *)&sockstruct, sizeof(struct sockaddr_in)) == -1) {
    perror("Bind failure");
    exit(EXIT_FAILURE);
  }

  while (true) {
    printf("Accepting new clients...\n");
    int connected_fd = accept(socket_fd, NULL, NULL);
    if (connected_fd == -1) {
      perror("Accept failure");
      exit(EXIT_FAILURE);
    }

    const int SIZE = 1024;
    char buff[SIZE];
    int bytes_read;
    while ((bytes_read = read(connected_fd, buff, SIZE)) > 0) {
      write(STDOUT_FILENO, buff, bytes_read);
    }
    if (bytes_read == -1) {
      perror("Read error");
      exit(EXIT_FAILURE);
    }
    close(connected_fd);
  }
}
