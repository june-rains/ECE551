#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid arguments!");
    exit(EXIT_FAILURE);
  }

  FILE * f = readFILE(argv[1]);
  int len = 0;
  size_t linecapp = 0;
  char * curr = NULL;
  while ((len = getline(&curr, &linecapp, f)) >= 0) {
    wordarray_t * line;
    wordarray_t * catname;
    line = split(curr);
    catname = searchCategory(line);
    line = replace(line, catname);
    print(line);
    freeWordArr(line);
    freeWordArr(catname);
    line = NULL;
    catname = NULL;
  }
  free(curr);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close the file!");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
