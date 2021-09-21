#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFilename\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Can not open the file");
    return EXIT_FAILURE;
  }

  char matrix[11][12];
  int row = 0;
  while (fgets(matrix[row], 12, f) != NULL) {
    if (strchr(matrix[row], '\n') - matrix[row] != 10) {
      perror("invalid number of characters in line!");
      return EXIT_FAILURE;
    }
    row++;
  }
  if (row != 10) {
    perror("invalid number of line!");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[9 - j][i]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
