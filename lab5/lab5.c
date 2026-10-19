#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *iblock, uint64_t size, struct header *next, int id) {
  iblock->size = size;
  iblock->next = next;
  iblock->id = id;
}

uint64_t absolute_difference(uint64_t a, uint64_t b);

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  while (free_list_ptr) {
    if (free_list_ptr->size >= size) {
      return free_list_ptr->id;
    } else {
      free_list_ptr = free_list_ptr->next;
    }
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t smallest_block_diff = UINT64_MAX;

  while (free_list_ptr) {
    if (free_list_ptr->size >= size) {
      uint64_t block_diff = free_list_ptr->size - size;
      if (block_diff < smallest_block_diff) {
        smallest_block_diff = block_diff;
        best_fit_id = free_list_ptr->id;
      }
    }
    free_list_ptr = free_list_ptr->next;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t largest_block_diff = 0;

  while (free_list_ptr) {
    if (free_list_ptr->size >= size) {
      uint64_t block_diff = free_list_ptr->size - size;
      if (block_diff > largest_block_diff) {
        largest_block_diff = block_diff;
        worst_fit_id = free_list_ptr->id;
      }
    }
    free_list_ptr = free_list_ptr->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs

  printf("ID for first_fit: %d\n", first_fit_id);
  printf("ID for best_fit: %d\n", best_fit_id);
  printf("ID for worst_fit: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

uint64_t absolute_difference(uint64_t a, uint64_t b) {
  if (a > b) {
    return a - b;
  } else {
    return b - a;
  }
}

/*
procedure: coalesce ()
  check if z end where n starts
  if yes merge

  check if next block ends where the next block after starts and merge if yes

  return when no more blocks
 * */
