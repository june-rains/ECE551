#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc > 4 || argc < 3) {
    fprintf(stderr, "Invalid use of arguments!");
    exit(EXIT_FAILURE);
  }
  /********NO ARGUMENTS -n*********/
  if (argc == 3) {
    int rm = 0;
    FILE * fwords = readFILE(argv[1]);
    FILE * fstory = readFILE(argv[2]);

    /**********STEP 2 FORM THE CATEGORY***********/
    catarray_t * ans = malloc(sizeof(*ans));
    ans->n = 0;
    ans->arr = NULL;
    char * curr1 = NULL;
    int len1 = 0;
    size_t linecapp1 = 0;
    char ** nameArray = NULL;
    int index = 0;
    while ((len1 = getline(&curr1, &linecapp1, fwords)) >= 0) {
      checkStep2(curr1);
      char * name = extractName(curr1);
      nameArray = realloc(nameArray, (index + 1) * sizeof(*nameArray));
      nameArray[index] = name;
      index++;
      char * word = extractWord(curr1);
      if (containName(name, ans) == 0) {
        addName(name, ans);
      }
      addWords(word, name, ans);
    }
    free(curr1);

    /*********STEP 1 FORM THE STORY***********/
    int len2 = 0;
    size_t linecapp2 = 0;
    char * curr2 = NULL;
    category_t * usedWords = malloc(sizeof(*usedWords));
    usedWords->name = NULL;
    usedWords->words = NULL;
    usedWords->n_words = 0;
    while ((len2 = getline(&curr2, &linecapp2, fstory)) >= 0) {
      checkStep1(curr2);
      wordarray_t * line;
      wordarray_t * catname;
      line = split(curr2);
      catname = searchCategory(line);
      line = replaceAll(line, catname, &ans, &usedWords, rm);
      print(line);
      freeWordArr(line);
      freeWordArr(catname);

      line = NULL;
      catname = NULL;
    }
    freeUsedWords(usedWords);
    free(curr2);
    freeNameArray(nameArray, index);
    freeArray(ans);
    fclose(fwords);
    fclose(fstory);
    return EXIT_SUCCESS;
  }
  /********ONE MORE ARGUMENTS -n*********/
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Invalid use of arguments!");
      exit(EXIT_FAILURE);
    }
    else {
      int rm = 1;
      FILE * fwords = readFILE(argv[2]);
      FILE * fstory = readFILE(argv[3]);

      /**********STEP 2 FORM THE CATEGORY***********/
      catarray_t * ans = malloc(sizeof(*ans));
      ans->n = 0;
      ans->arr = NULL;
      char * curr1 = NULL;
      int len1 = 0;
      size_t linecapp1 = 0;
      char ** nameArray = NULL;
      int index = 0;
      while ((len1 = getline(&curr1, &linecapp1, fwords)) >= 0) {
        checkStep2(curr1);
        char * name = extractName(curr1);
        nameArray = realloc(nameArray, (index + 1) * sizeof(*nameArray));
        nameArray[index] = name;
        index++;
        char * word = extractWord(curr1);
        if (containName(name, ans) == 0) {
          addName(name, ans);
        }
        addWords(word, name, ans);
      }
      free(curr1);

      /*********STEP 1 FORM THE STORY***********/
      int len2 = 0;
      size_t linecapp2 = 0;
      char * curr2 = NULL;
      category_t * usedWords = malloc(sizeof(*usedWords));
      usedWords->name = NULL;
      usedWords->words = NULL;
      usedWords->n_words = 0;
      while ((len2 = getline(&curr2, &linecapp2, fstory)) >= 0) {
        checkStep1(curr2);
        wordarray_t * line;
        wordarray_t * catname;
        line = split(curr2);
        catname = searchCategory(line);
        line = replaceAll(line, catname, &ans, &usedWords, rm);
        print(line);
        freeWordArr(line);
        freeWordArr(catname);
        line = NULL;
        catname = NULL;
      }
      freeUsedWords(usedWords);
      free(curr2);
      freeNameArray(nameArray, index);
      freeArray(ans);
      fclose(fwords);
      fclose(fstory);
      return EXIT_SUCCESS;
    }
  }
}
