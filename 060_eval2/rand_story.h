#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
void checkStep1(char * curr);
void checkStep2(char * curr);
wordarray_t * split(char * line);
wordarray_t * searchCategory(wordarray_t * arr);
char * replaceOne(char * old, char * word);
wordarray_t * replace(wordarray_t * arr, wordarray_t * catarr);
void print(wordarray_t * arr);
void freeWordArr(wordarray_t * arr);
FILE * readFILE(char * filename);
char * extractName(char * line);
char * extractWord(char * line);
int containName(char * name, catarray_t * ans);
void addName(char * name, catarray_t * ans);
void addWords(char * word, char * name, catarray_t * ans);
void freeArray(catarray_t * ans);
void freeNameArray(char ** nameArray, int index);
void freeUsedWords(category_t * usedWords);
catarray_t * storeWords(FILE * f, char *** nameArray, catarray_t * ans, int * index);
wordarray_t * replaceAll(wordarray_t * arr,
                         wordarray_t * catarr,
                         catarray_t ** ans,
                         category_t ** usedWords,
                         int rm);

#endif
