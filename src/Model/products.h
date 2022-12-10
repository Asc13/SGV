#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Products_H
#define Products_H

typedef struct products* Products;

#define ASCII 65
#define TAM 26


Products initProducts();

void addProduct(Products products, char* id);

int searchProduct(Products products, char* id);

int getNumProducts(Products products);

#endif