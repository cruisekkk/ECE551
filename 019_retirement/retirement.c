#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return; 
};

typedef struct _retire_info retire_info;

void retirement (int startAge, double initial, retire_info working, retire_info retired); 

  

int  main (){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
  
}



void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double balance;
  balance = initial;
  int month = startAge;
  int fix_month = startAge;
  int age = month /12;
  int month12 = month % 12;
  for (; month < fix_month +  working.months; month++){
    age = month / 12;
    month12 = month % 12;
    printf("Age %3d month %2d you have $%.2lf\n ", age, month12, balance);
    double increase = balance * working.rate_of_return/12;
    balance = balance + increase;
    balance = balance + working.contribution;
  }
  
  int retire_month = month;
  for (; month < retire_month + retired.months; month++){
    age = month / 12;
    month12 = month % 12;
    printf("Age %3d month %2d you have $%.2lf\n ", age, month12, balance);
    double decrease = balance * retired.rate_of_return/12;
    balance = balance + decrease;
    balance = balance + retired.contribution;
  }

  
 
}
