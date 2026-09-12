#include <stdio.h>
#include <time.h>

/*
 * Code for date logicborroed from Kernighan & Richie's
 * "The C Programming Language" (255-256) and W3School's
 * C Date and Time tutorial: https://w3schools.com/c/c_date_time.php
 */

int main() {
  printf("Hello World!\n");

  time_t current_time = time(NULL);
  struct tm *local_time = localtime(&current_time);
  char buffer[100];

  strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", local_time);

  printf("Today's date is: %s\n", buffer);
}
