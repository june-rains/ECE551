#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    printf("not a valid function!");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(2, 0, 1);
  run_check(2.1, 2.1, 4);
  run_check(-2, 2, 4);
  run_check(-1, 1, 4294967295);
  return EXIT_SUCCESS;
}
