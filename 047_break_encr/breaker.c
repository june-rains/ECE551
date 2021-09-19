#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int count(FILE * f) {
  //这种方法可以初始化所有的数组元素为0
  int arr[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      arr[c - 'a'] += 1;
    }
  }

  int max = 0;
  int currMax = arr[0];
  //注意要更新比较的数
  /*或者可以写成:
  for (int i = 0; i < 25; i++) {
    if (arr[max] < arr[i + 1]) {
      max = i + 1;
    }
  }
  */
  for (int i = 1; i < 26; i++) {
    if (currMax < arr[i]) {
      max = i;
      currMax = arr[i];
    }
  }
  return max;
}

int breaker(FILE * f) {
  int max = count(f);
  int key;
  key = (max + 26 - 4) % 26;
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = breaker(f);
  if (key >= 26 || key < 0) {
    printf("No answer! Fail!");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
