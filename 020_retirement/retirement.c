#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double compute_print(int currmonth, double currsaving, retire_info info) {
  int age = currmonth / 12;
  int month = currmonth % 12;
  currsaving = currsaving + currsaving * info.rate_of_return + info.contribution;
  printf("Age %3d month %2d you have $%.2lf\n", age, month, currsaving);
  return currsaving;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double saving = initial;
  printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
  for (int i = startAge + 1; i < startAge + working.months + retired.months; i++) {
    if (i <= startAge + working.months) {
      saving = compute_print(i, saving, working);
    }
    else {
      saving = compute_print(i, saving, retired);
    }
  }
}

int main(void) {
  double initial = 21345;
  int startAge = 327;
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
