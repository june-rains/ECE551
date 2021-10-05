#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->unknown_counts = 0;
  counts->strs = NULL;
  counts->len = 0;
  return counts;
}

int find_string(counts_t * c, const char * name) {
  for (int i = 0; i < c->len; i++) {
    if (strcmp(name, c->strs[i].str) == 0) {
      c->strs[i].counts++;
      return 1;
    }
  }
  return 0;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //unknown case
  if (name == NULL) {
    c->unknown_counts++;
    return;
  }
  //normal case
  if (!find_string(c, name)) {
    c->strs = realloc(c->strs, (c->len + 1) * sizeof(*(c->strs)));
    size_t sz = strlen(name) + 1;
    c->strs[c->len].str = strndup(name, sz);
    c->strs[c->len].counts = 1;
    c->len++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->strs[i].str, c->strs[i].counts);
  }
  if (c->unknown_counts != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknown_counts);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->len; i++) {
    free(c->strs[i].str);
  }
  free(c->strs);
  free(c);
}
