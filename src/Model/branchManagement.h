#ifndef BranchManagement_H
#define BranchManagement_H

#define BRANCHES 3

typedef struct branchManagement* BranchManagement;


BranchManagement initBranchManagement();

void addSaleToBranch(BranchManagement branchManagement, int branch, char* id, 
                     char* product, int month, double price, int quantity, char mode);

int getNumberSales(BranchManagement branchManagement);

void getClientsOfAllBranchesHelper(BranchManagement branchManagement, char** clients, int* isOnBranches, int number_clients);

void getProductsStatsBoughtByClientHelper(BranchManagement branchManagement, char* id, int* content);

int getClientThatNeverBoughtCount(BranchManagement branchManagement);

#endif