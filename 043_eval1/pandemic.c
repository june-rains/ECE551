#include "pandemic.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//define the maximum unsinged long integer to help
#define UINT_MAX64 18446744073709551615U

country_t parseLine(char * line) {
  //WRITE ME
  //Declare variables
  country_t ans;
  char * p1 = strchr(line, ',');
  char * p2 = strchr(line, '\n');
  int name_length = p1 - line;
  int popu_length = p2 - p1 - 1;
  char population[popu_length + 1];

  //judge input error for population size
  if (popu_length < 1) {
    fprintf(stderr, "invalid population form!");
    exit(EXIT_FAILURE);
  }
  //judge input error for name size
  if (name_length > 63) {
    fprintf(stderr, "Invalid size of country name!");
    exit(EXIT_FAILURE);
  }
  //copy into ans.name
  for (int i = 0; i < name_length; i++) {
    ans.name[i] = *line;
    line++;
  }
  ans.name[name_length] = '\0';

  //copy into ans.population
  p1++;  //use pointer p1 to copy population number
  for (int j = 0; j < popu_length; j++) {
    population[j] = *p1;
    p1++;
  }
  population[popu_length] = '\0';
  char * endptr;
  //judge error case: invalid population representation
  if (strtoul(population, &endptr, 10) == 0) {
    fprintf(stderr, "Can not represent population with valid number!");
    exit(EXIT_FAILURE);
  }
  uint64_t result = strtoul(population, &endptr, 10);
  //judge error case: big number
  if (result == UINT_MAX64 && errno == ERANGE) {
    fprintf(stderr, "Too Big Population Number!");
    exit(EXIT_FAILURE);
  }

  ans.population = strtoul(population, &endptr, 10);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  //check n_days, if n_days < 7, do nothing
  if (n_days < 7) {
    return;
  }

  //n_days >= 7, compute avg as usual
  double total = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    total = 0;
    for (size_t j = i; j < i + 7; j++) {
      total += data[j];
    }
    avg[i] = total / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //check n_days, if n_days < 1, do nothing
  if (n_days < 1) {
    return;
  }

  //n_days >= 1, compute as usual
  double total = 0;
  for (size_t i = 0; i < n_days; i++) {
    if (pop == 0) {
      cum[i] = INFINITY;
    }
    total += data[i];
    cum[i] = (total * 100000) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  //check n_countries and n_days, if either of them smaller than 1, do nothing
  if (n_countries < 1 || n_days < 1) {
    return;
  }

  //if n_countries and n_days > 1, then compute as usual
  unsigned max[n_countries];
  for (size_t i = 0; i < n_countries; i++) {
    max[i] = data[i][0];
    for (size_t j = 1; j < n_days; j++) {
      if (max[i] <= data[i][j]) {
        max[i] = data[i][j];
      }
    }
  }
  size_t country_num = 0;
  for (size_t i = 1; i < n_countries; i++) {
    if (max[country_num] == max[i]) {
      printf("There is a tie between at least two countries");
      return;
    }
    if (max[country_num] < max[i]) {
      country_num = i;
    }
  }
  printf("%s has the most daily cases with %u\n",
         countries[country_num].name,
         max[country_num]);
}
