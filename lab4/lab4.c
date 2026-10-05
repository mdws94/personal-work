#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define EXTRA_SIZE 256 // num in bytes
#define BUFF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void initialize_block(struct header *, uint64_t size, struct header *next);
void print_out(char *format, void *data, size_t data_size);

int main() {
  void *program_break = sbrk(EXTRA_SIZE);

  if (program_break == (void *)-1) {
    perror("sbrk failure");
    return 1;
  }

  struct header *first_block_header = (struct header *)program_break;
  struct header *second_block_header = (struct header *)(program_break + 128);

  initialize_block(first_block_header, 128, NULL);
  initialize_block(second_block_header, 128, first_block_header);

  return 0;
}

void initialize_block(struct header *header, uint64_t size, struct header *next) {
  header->size = size;
  header->next = next;
}

void print_out(char *format, void *data, size_t data_size) {
  char buff[BUFF_SIZE];
  ssize_t len = snprintf(buff, BUFF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    // handle_error("snprintf");
  }

  write(STDOUT_FILENO, buff, len);
}
