#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid arguments!");
    exit(EXIT_FAILURE);
  }
  FILE * f = readFILE(argv[1]);

  catarray_t * ans = malloc(sizeof(*ans));
  ans->n = 0;
  ans->arr = NULL;
  char * curr = NULL;
  int len = 0;
  size_t linecapp = 0;
  char ** nameArray = NULL;
  int index = 0;
  while ((len = getline(&curr, &linecapp, f)) >= 0) {
    checkStep2(curr);
    char * name = extractName(curr);
    nameArray = realloc(nameArray, (index + 1) * sizeof(*nameArray));
    nameArray[index] = name;
    index++;
    char * word = extractWord(curr);
    if (containName(name, ans) == 0) {
      addName(name, ans);
    }
    addWords(word, name, ans);
  }

  free(curr);
  printWords(ans);
  freeArray(ans);
  freeNameArray(nameArray, index);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close the file");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
