#include "rand_story.h"

#include "provided.h"

void checkStep1(char * curr) {
  int num = 0;
  char * p = curr;
  while (*p != '\0') {
    if (*p == '_') {
      num++;
    }
    p++;
  }

  if (num % 2 != 0) {
    fprintf(stderr, "Invalid format of underscore!");
    exit(EXIT_FAILURE);
  }
}

void checkStep2(char * curr) {
  if (strchr(curr, ':') == NULL) {
    fprintf(stderr, "Invalid format of input file! one line has no colon!");
    exit(EXIT_FAILURE);
  }
}

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

wordarray_t * replaceAll(wordarray_t * arr,
                         wordarray_t * catarr,
                         catarray_t ** ans,
                         category_t ** usedWords,
                         int rm) {
  (*usedWords)->name = NULL;
  (*usedWords)->words = NULL;
  (*usedWords)->n_words = 0;
  for (size_t i = 0; i < catarr->n; i++) {
    char * result;
    char * p1 = strchr(arr->wordArr[catarr->mark[i]], '_');
    char * p2 = strchr(p1 + 1, '_');
    char * rest = p2 + 1;
    int restlen = strlen(rest);
    const char * new = NULL;
    if (atoi(catarr->wordArr[i]) == 0) {
      new = strdup(chooseWord(catarr->wordArr[i], *ans));
      (*usedWords)->words =
          realloc((*usedWords)->words,
                  ((*usedWords)->n_words + 1) * sizeof(*(*usedWords)->words));
      (*usedWords)->words[(*usedWords)->n_words] = strdup(new);
      (*usedWords)->n_words++;
      if (rm == 1) {
        for (size_t m = 0; m < (*ans)->n; m++) {
          if (strcmp((*ans)->arr[m].name, catarr->wordArr[i]) == 0) {
            if ((*ans)->arr[m].n_words == 0) {
              fprintf(stderr, "words are used up! no more words!");
              exit(EXIT_FAILURE);
            }
            for (size_t n = 0; n < (*ans)->arr[m].n_words; n++) {
              if (strcmp((*ans)->arr[m].words[n], new) == 0) {
                free((*ans)->arr[m].words[n]);
                (*ans)->arr[m].words[n] = NULL;
                for (size_t k = n; k < (*ans)->arr[m].n_words - 1; k++) {
                  (*ans)->arr[m].words[k] = (*ans)->arr[m].words[k + 1];
                }
                (*ans)->arr[m].words =
                    realloc((*ans)->arr[m].words,
                            ((*ans)->arr[m].n_words - 1) * sizeof(*(*ans)->arr[m].words));
                (*ans)->arr[m].n_words--;
                /*
                free((*ans)->arr[m].words[n]);
                (*ans)->arr[m].words[n] = NULL;
                (*ans)->arr[m].n_words--;
		*/
              }
            }
          }
        }
      }
    }
    else if (atoi(catarr->wordArr[i]) >= 1 &&
             atoi(catarr->wordArr[i]) <= (int)(*usedWords)->n_words) {
      new = strdup((*usedWords)->words[(*usedWords)->n_words - atoi(catarr->wordArr[i])]);
      (*usedWords)->words =
          realloc((*usedWords)->words,
                  ((*usedWords)->n_words + 1) * sizeof(*(*usedWords)->words));
      (*usedWords)->words[(*usedWords)->n_words] = strdup(new);
      (*usedWords)->n_words++;
    }

    else {
      fprintf(stderr, "Invalid format of the category reference number!");
      exit(EXIT_FAILURE);
    }

    int newlen = strlen(new);
    if (restlen == 0) {
      result = strdup(new);
    }
    else {
      result = malloc((restlen + newlen + 1) * sizeof(*result));
      strncpy(result, new, newlen + 1);
      result = strcat(result, rest);
    }

    free(arr->wordArr[catarr->mark[i]]);
    arr->wordArr[catarr->mark[i]] = result;
    free((char *)new);
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
      /*
      if (ans->arr[i].words[j] == NULL) {
        ans->arr[i].n_words++;
      }
      else {
        free(ans->arr[i].words[j]);
      }
      */
    }

    free(ans->arr[i].words);
  }

  free(ans->arr);
  free(ans);
}

void freeNameArray(char ** nameArray, int index) {
  for (int i = 0; i < index; i++) {
    free(nameArray[i]);
  }

  free(nameArray);
}

void freeUsedWords(category_t * usedWords) {
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords);
  usedWords = NULL;
}
