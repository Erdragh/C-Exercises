#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int integer_compare(void const * a, void const * b) {
  int const *el_a = (int const *) a;
  int const *el_b = (int const *) b;
  if (*el_a < *el_b) {
    return -1;
  } else if (*el_a == *el_b) {
    return 0;
  } else {
    return 1;
  }
}

int main() {
  int buf[SIZE];

  srand(1234123412);

  for (int i = 0; i < SIZE; i++) {
    buf[i] = rand() % 999;
  }

  qsort(buf, SIZE, sizeof(int), integer_compare);

  for (int i = 0; i < SIZE; i++) {
    printf("%d\n", buf[i]);
  }
  if (fflush(stdout) == EOF) {
    perror("fflush");
    exit(EXIT_FAILURE);
  }
}