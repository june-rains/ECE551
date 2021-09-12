#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }

  size_t countMax = 1, count = 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      count++;
    }
    else {
      count = 1;
    }

    if (count >= countMax) {
      countMax = count;
    }
  }
  return countMax;
}
