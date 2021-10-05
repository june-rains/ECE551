#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * read_kv_from_string(const char * str, const int len) {
  kvpair_t * kv_pair = malloc(sizeof(*kv_pair));
  kv_pair->key = NULL;
  kv_pair->value = NULL;
  for (int i = 0; i < len; i++) {
    if (str[i] == '=') {
      kv_pair->key = strndup(str, i);
      kv_pair->value = strndup(str + i + 1, len - i - 2);
      break;
    }
  }
  return kv_pair;
}

kvarray_t * read_kv_from_file(FILE * f) {
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->kv_array = NULL;
  ans->length = 0;  // the count of kv pairs
  int len = 0;      // the length of current string
  char * str = NULL;
  size_t sz = 0;

  while ((len = getline(&str, &sz, f)) != EOF) {
    kvpair_t * kv_pair = read_kv_from_string(str, len);
    ans->kv_array = realloc(ans->kv_array, ++ans->length * sizeof(*(ans->kv_array)));
    ans->kv_array[ans->length - 1] = kv_pair;
  }
  free(str);
  return ans;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "No such file.\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * ans = read_kv_from_file(f);

  if (fclose(f)) {
    fprintf(stderr, "Can not close file.\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->kv_array[i]->key);
    free(pairs->kv_array[i]->value);
    free(pairs->kv_array[i]);
  }
  free(pairs->kv_array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    fprintf(stdout,
            "key = '%s' value = '%s'\n",
            pairs->kv_array[i]->key,
            pairs->kv_array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    if (!strcmp(pairs->kv_array[i]->key, key)) {
      return pairs->kv_array[i]->value;
    }
  }
  return NULL;
}
/*
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
*/
