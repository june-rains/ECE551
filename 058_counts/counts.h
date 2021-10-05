#ifndef __COUNTS_H__
#define __COUNTS_H__
#include <stdio.h>
/*
struct _one_count_t {
  //DEFINE ME
  int count;
  char * str;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t * arr;
  int n;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);
*/

struct _one_count_t {
  //DEFINE ME
  char * str;
  int counts;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t * strs;
  int len;
  int unknown_counts;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
