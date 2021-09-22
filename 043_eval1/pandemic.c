#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  //Declare variable
  country_t ans;
  char * p1 = strchr(line, ',');
  char * p2 = strchr(line, '\n');
  int name_length = p1 - line;
  int popu_length = p2 - p1 - 1;
  char population[popu_length + 1];
  //judge input error for name
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
  p1++;
  for (int j = 0; j < popu_length; j++) {
    if ((*p1) < 48 || (*p1) > 57) {
      fprintf(stderr, "Can not represent population with number!");
      exit(EXIT_FAILURE);
    }
    population[j] = *p1;
    p1++;
  }
  population[popu_length] = '\0';
  ans.population = atoi(population);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
