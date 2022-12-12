#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Branch_H
#define Branch_H

#define ASCII 65
#define TAM 26


typedef struct branch* Branch;


Branch initBranch();

void updateBranchEntry(Branch branch, char* id, char* product, int month, double price, int quantity, char mode);

int isOnBranch(Branch branch, char* id);

void getProductsStatsBoughtByClientOnBranch(Branch branch, int branchID, char* id, int* content);

void getClientThatNeverBoughtCountOnBranch(Branch branch, int* count);

#endif