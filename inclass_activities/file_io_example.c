#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_NAME "tmp"
#define MAX_SIZE 1024

int main() {
  const char *pth = PATH_NAME;

  int fd = open(pth, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("Open error");
    exit(EXIT_FAILURE);
  }

  const char *msg = "Hello World!";
  size_t len = strlen(msg);
  ssize_t num_written = 0;

  while (num_written < len) {
    ssize_t bytes_written = write(fd, msg + num_written, len - num_written);
    if (bytes_written == -1) {
      perror("Write error");
      close(fd);
      exit(EXIT_FAILURE);
    }

    num_written += (size_t)bytes_written;
  }

  off_t ofst = lseek(fd, -((ssize_t)len) / 2, SEEK_CUR);
  if (ofst == -1) {
    perror("lseek error");
    close(fd);
    exit(EXIT_FAILURE);
  }

  char buff[MAX_SIZE];
  ssize_t bytes_read = 0;

  while ((bytes_read = read(fd, buff, sizeof(buff) - 1)) > 0) {
    buff[bytes_read] = '\0';
    printf("%s", buff);
  }
  printf("\n");

  if (close(fd) == -1) {
    perror("Error closing file");
    exit(EXIT_FAILURE);
  }

  return 0;
}
