#include "rand_story.h"

#include "provided.h"

wordarray_t * split(char * line) {
  wordarray_t * arr = malloc(sizeof(*arr));
  char * word;
  char * wordcpy;
  char * delim = " ";
  word = strtok(line, delim);
  wordcpy = strdup(word);
  arr->wordArr = malloc(sizeof(*arr->wordArr));
  arr->n = 1;
  arr->wordArr[arr->n - 1] = wordcpy;
  arr->mark = 0;
  while ((word = strtok(NULL, delim)) != NULL) {
    arr->wordArr = realloc(arr->wordArr, (arr->n + 1) * sizeof(*arr->wordArr));
    arr->wordArr[arr->n] = strdup(word);
    arr->n++;
  }
  return arr;
}

wordarray_t * searchCategory(wordarray_t * arr) {
  wordarray_t * ans = malloc(sizeof(*ans));
  ans->wordArr = NULL;
  ans->mark = 0;
  ans->n = 0;
  for (size_t i = 0; i < arr->n; i++) {
    if (strchr(arr->wordArr[i], '_') != NULL) {
      char * p1 = strchr(arr->wordArr[i], '_');
      char * p2 = strchr(p1 + 1, '_');
      int len = p2 - p1 - 2;
      ans->wordArr = realloc(ans->wordArr, (ans->n + 1) * sizeof(ans->wordArr));
      ans->wordArr[ans->n] = strndup(arr->wordArr[i] + 1, len + 1);
      ans->mark = realloc(ans->mark, (ans->n + 1) * sizeof(*ans->mark));
      ans->mark[ans->n] = i;
      ans->n++;
    }
  }
  return ans;
}

char * replaceOne(char * old, char * word) {
  char * result;
  char * p1 = strchr(word, '_');
  char * p2 = strchr(p1 + 1, '_');
  char * rest = p2 + 1;
  int restlen = strlen(rest);
  const char * new = chooseWord(old, NULL);
  int newlen = strlen(new);
  if (restlen == 0) {
    result = strdup(new);
  }
  else {
    result = malloc((restlen + newlen + 1) * sizeof(*result));
    strncpy(result, new, newlen + 1);
    result = strcat(result, rest);
  }
  return result;
}

wordarray_t * replace(wordarray_t * arr, wordarray_t * catarr) {
  for (size_t i = 0; i < catarr->n; i++) {
    char * new = replaceOne(catarr->wordArr[i], arr->wordArr[catarr->mark[i]]);
    free(arr->wordArr[catarr->mark[i]]);
    arr->wordArr[catarr->mark[i]] = new;
  }
  return arr;
}

void print(wordarray_t * arr) {
  for (size_t i = 0; i < arr->n - 1; i++) {
    printf("%s ", arr->wordArr[i]);
  }
  printf("%s", arr->wordArr[arr->n - 1]);
}

void freeWordArr(wordarray_t * arr) {
  for (size_t i = 0; i < arr->n; i++) {
    free(arr->wordArr[i]);
  }
  free(arr->wordArr);
  free(arr->mark);
  free(arr);
}

FILE * readFILE(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open the file!");
    exit(EXIT_FAILURE);
  }
  return f;
}

char * extractName(char * line) {
  char * name;
  char * p = strchr(line, ':');
  int len = p - line;
  name = strndup(line, len);
  return name;
}

char * extractWord(char * line) {
  char * word;
  char * p1 = strchr(line, ':');
  char * p2 = strchr(line, '\n');
  p1 = p1 + 1;
  int len = p2 - p1;
  word = strndup(p1, len);
  return word;
}

int containName(char * name, catarray_t * ans) {
  size_t i = 0;
  for (i = 0; i < ans->n; i++) {
    if (strcmp(ans->arr[i].name, name) == 0) {
      return 1;
    }
  }
  return 0;
}

void addName(char * name, catarray_t * ans) {
  ans->arr = realloc(ans->arr, (ans->n + 1) * sizeof(*ans->arr));
  ans->arr[ans->n].name = name;
  ans->arr[ans->n].n_words = 0;
  ans->arr[ans->n].words = NULL;
  ans->n++;
}

void addWords(char * word, char * name, catarray_t * ans) {
  for (size_t i = 0; i < ans->n; i++) {
    if (strcmp(ans->arr[i].name, name) == 0) {
      ans->arr[i].words = realloc(ans->arr[i].words,
                                  (ans->arr[i].n_words + 1) * sizeof(*ans->arr[i].words));
      ans->arr[i].words[ans->arr[i].n_words] = word;
      ans->arr[i].n_words++;
    }
  }
}

void freeArray(catarray_t * ans) {
  for (size_t i = 0; i < ans->n; i++) {
    for (size_t j = 0; j < ans->arr[i].n_words; j++) {
      free(ans->arr[i].words[j]);
    }
    free(ans->arr[i].words);
    // free(ans->arr[i].name);
  }

  free(ans->arr);
  free(ans);
}

catarray_t * storeWords(FILE * f, char *** nameArray, catarray_t * ans, int * index) {
  char * curr = NULL;
  int len = 0;
  size_t linecapp = 0;
  while ((len = getline(&curr, &linecapp, f)) >= 0) {
    char * name = extractName(curr);
    *nameArray = realloc(*nameArray, (*index + 1) * sizeof(**nameArray));
    *nameArray[*index] = name;
    *index = *index + 1;
    char * word = extractWord(curr);
    if (containName(name, ans) == 0) {
      addName(name, ans);
    }
    addWords(word, name, ans);
  }

  free(curr);
  return ans;
}
/*
char ** storeNameArr(FILE * f, char ** nameArray, catarray * ans) {
  char * curr = NULL;
  int len = 0;
  size_t linecapp = 0;
  char ** nameArray = NULL;
  int index = 0;
  while ((len = getline(&curr, &linecapp, f)) >= 0) {
    char * name = extractName(curr);
    nameArray = realloc(nameArray, (index + 1) * sizeof(*nameArray));
    nameArray[index] = name;
    index++;
  }
  return nameArray;
}

int storeNameArrsz(FILE * f) {
  char * curr = NULL;
  int len = 0;
  size_t linecapp = 0;
  int index = 0;
  while ((len = getline(&curr, &linecapp, f)) >= 0) {
    index++;
  }
  return index;
}
*/
