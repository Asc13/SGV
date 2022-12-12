#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef BranchEntry_H
#define BranchEntry_H


typedef struct branchEntry* BranchEntry;


BranchEntry initBranchEntry();

void updateSalesEntry(BranchEntry branchEntry, char* product, int month, double price, int quantity, char mode);

void getAllQuantitiesFromBranchEntryByBranch(BranchEntry branchEntry, int branch, int* content);

int getNumberCodes(BranchEntry branchEntry);

#endif