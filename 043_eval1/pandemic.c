#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  //Declare variables
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
  p1++;  //use pointer p1 to copy population number
  for (int j = 0; j < popu_length; j++) {
    //judge input error for invalid population representation
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
  double total = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    for (size_t j = i; j < i + 7; j++) {
      total += data[j];
    }
    avg[i] = total / 7;
  }
  //考虑n_days大于7或者小于7?
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double total = 0;
  for (size_t i = 0; i < n_days; i++) {
    total += data[i];
    cum[i] = (total * 100000) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
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
