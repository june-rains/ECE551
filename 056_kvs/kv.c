#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * split(char * kv, size_t size) {
  kvpair_t * result = malloc(size * sizeof(*result));
  result->key = NULL;
  result->value = NULL;
  for (size_t i = 0; i < size; i++) {
    if (kv[i] == '=') {
      result->key = strndup(kv, i);
      result->value = strndup(kv + i + 1, size - i - 2);
      break;
    }
  }
  return result;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->kvs = NULL;
  answer->n_kvs = 0;
  int len = 0;
  char * curr = NULL;
  size_t linecap = 0;
  //Open the input file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open the file!");
    exit(EXIT_FAILURE);
  }
  //Read the lines of input file
  while ((len = getline(&curr, &linecap, f)) >= 0) {
    kvpair_t * kv_pair = split(curr, len);
    answer->kvs = realloc(answer->kvs, (answer->n_kvs + 1) * sizeof(answer->kvs));
    answer->kvs[answer->n_kvs] = kv_pair;
    answer->n_kvs++;
  }

  free(curr);

  //Close the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    exit(EXIT_FAILURE);
  }

  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->n_kvs; i++) {
    free(pairs->kvs[i]->key);
    free(pairs->kvs[i]->value);
    free(pairs->kvs[i]);
  }
  free(pairs->kvs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->n_kvs; i++) {
    printf("key = '%s', value = '%s'\n", pairs->kvs[i]->key, pairs->kvs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->n_kvs; i++) {
    if (strcmp(pairs->kvs[i]->key, key) == 0) {
      return pairs->kvs[i]->value;
    }
  }
  return NULL;
}
