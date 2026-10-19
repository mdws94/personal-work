#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXTRA_SIZE 256 // num in bytes
#define BLOCK_SIZE 128
#define BUFF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void initialize_block(struct header *, uint64_t size, struct header *next, int data);
void handle_error(const char *err);
void print_out(char *format, void *data, size_t data_size);
void print_block(char *block_start);

int main() {
  void *program_break = sbrk(EXTRA_SIZE);

  if (program_break == (void *)-1) {
    handle_error("sbrk failure");
  }

  struct header *first_block_header = (struct header *)program_break; // Pointers point to allocated
                                                                      // memory
  struct header *second_block_header = (struct header *)(program_break + 128);

  initialize_block(first_block_header, BLOCK_SIZE, NULL, 0);
  initialize_block(second_block_header, BLOCK_SIZE, first_block_header, 1);

  print_out("First block: %p\n", &first_block_header, sizeof(first_block_header));
  print_out("First block size: %lu\n", &first_block_header->size, sizeof(first_block_header->size));
  print_block((char *)first_block_header);

  write(1, "\n", 1);

  print_out("Second block: %p\n", &second_block_header, sizeof(second_block_header));
  print_out("Second block size: %lu\n", &second_block_header->size,
            sizeof(second_block_header->size));
  print_block((char *)second_block_header);
  return 0;
}

void initialize_block(struct header *header, uint64_t size, struct header *next, int data) {
  header->size = size;
  header->next = next;

  void *data_start = header + 1;
  size_t data_block_size = size - sizeof(struct header);
  memset(data_start, data, data_block_size);
}

void handle_error(const char *err) {
  perror(err);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buff[BUFF_SIZE];
  ssize_t len = snprintf(buff, BUFF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }

  write(STDOUT_FILENO, buff, len);
}

void print_block(char *block_start) {
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); ++i) {
    char *address = block_start + sizeof(struct header) + i;
    uint64_t val = (uint64_t)*address;
    if ((i) % 16 == 0) {
      write(1, "\n", 1);
    }
    print_out("%lu ", &val, sizeof(val));
  }
  write(1, "\n", 1);
}
