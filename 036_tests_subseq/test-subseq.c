#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t ans = maxSeq(array, n);
  if (ans != expected_ans) {
    printf("not a valid function!");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int array2[] = {-3, -2, -1};
  int array3[] = {-1, 0};
  int array4[] = {0};
  int array5[] = {'a', 'b', 'c'};
  int array6[] = {1, 0, 0, 1, 1};
  run_check(array1, 10, 4);
  run_check(array2, 3, 3);
  run_check(array3, 2, 2);
  run_check(array3, 4, 2);
  run_check(array4, 1, 1);
  run_check(array5, 3, 3);
  run_check(array6, 5, 2);
  run_check(array6, 0, 0);
  run_check(NULL, 0, 0);
  return EXIT_SUCCESS;
}
