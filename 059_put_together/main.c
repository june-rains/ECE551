#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * results = createCounts();
  //open the file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file!");
    exit(EXIT_FAILURE);
  }
  //read the file
  char * curr = NULL;
  char * line = NULL;
  int len = 0;
  size_t linecap = 0;
  int inputsz = 0;
  while ((len = getline(&curr, &linecap, f)) >= 0) {
    line = realloc(line, len * sizeof(*line));
    strncpy(line, curr, len - 1);
    line[len - 1] = '\0';
    for (size_t i = 0; i < kvPairs->n_kvs; i++) {
      if (strcmp(kvPairs->kvs[i]->key, line) == 0) {
        addCount(results, kvPairs->kvs[i]->value);
      }
    }
    inputsz++;
  }
  int size = 0;
  for (int i = 0; i < results->len; i++) {
    size = size + results->strs[i].counts;
  }
  results->unknown_counts = inputsz - size;
  free(line);
  free(curr);
  return results;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "invalide use of program!");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close the file!");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
