#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  size_t new_len = len + 8;
  char * result = malloc(new_len * sizeof(*result));
  result = strcpy(result, inputName);
  result[len] = '.';
  result[len + 1] = 'c';
  result[len + 2] = 'o';
  result[len + 3] = 'u';
  result[len + 4] = 'n';
  result[len + 5] = 't';
  result[len + 6] = 's';
  result[len + 7] = '\0';
  return result;
}
