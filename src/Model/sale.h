#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Sale_H
#define Sale_H


#define MONTHS 12

typedef struct sale* Sale;


Sale initSale(int month, double price, int quantity, char mode);

void updateWithSaleMonthAndQuantity(Sale sale, int branch, int* content);

#endif