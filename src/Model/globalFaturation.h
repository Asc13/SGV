#include <omp.h>

#ifndef GlobalFaturation_H
#define GlobalFaturation_H

typedef struct globalFaturation* GlobalFaturation;

#define ASCII 65
#define TAM 26

GlobalFaturation initGlobalFaturation();

void addProductToGlobalFaturation(GlobalFaturation globalFaturation, char* id);

void updateProductFat(GlobalFaturation globalFaturation, char* id, int branch, int month, 
                      double price, int quantity, char mode);

char** getProductsNeverBoughtHelper(GlobalFaturation globalFaturation, int branch, int* count);

int getNeverBoughtProductCount(GlobalFaturation globalFaturation);

void getFatAndSalesByMonths(GlobalFaturation globalFaturation, int minMonth, int maxMonth, int* count, double* fat);

#endif