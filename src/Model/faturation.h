#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Faturation_H
#define Faturation_H

#define MONTHS 12
#define BRANCHES 3
#define MODES 2

typedef struct faturation* Faturation;


Faturation initFaturation();

void addFaturation(Faturation faturation, int branch, int month, double price, int quantity, char mode);

double getFatByBranch(Faturation faturation, int branch);

double getFatByBranchAndMonth(Faturation faturation, int branch, int month);

double getFatByMonth(Faturation faturation, int month);

int neverBought(Faturation faturation, int branch);

void updateWithStatsByMonth(Faturation faturation, int minMonth, int maxMonth, int* count, double* fat);

#endif