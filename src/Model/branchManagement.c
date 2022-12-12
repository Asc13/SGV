#include "branchManagement.h"
#include "branch.h"
#include "rbt.h"


struct branchManagement {
    Branch* branches;
    int* number_sales;
};


BranchManagement initBranchManagement() {
    BranchManagement branchManagement = (BranchManagement) malloc(sizeof(struct branchManagement));
    branchManagement->branches = (Branch*) malloc(BRANCHES * sizeof(Branch));
    branchManagement->number_sales = (int*) malloc(BRANCHES * sizeof(int));

    for(int i = 0; i < BRANCHES; i++) {
        branchManagement->branches[i] = initBranch();
        branchManagement->number_sales[i] = 0;
    }

    return branchManagement;
}


void addSaleToBranch(BranchManagement branchManagement, int branch, char* id, char* product, int month, double price, int quantity, char mode) {    
    updateBranchEntry(branchManagement->branches[branch - 1], id, product, month, price, quantity, mode);
    branchManagement->number_sales[branch - 1]++;
}


int getNumberSales(BranchManagement branchManagement) {
    int count = 0;

    for(int i = 0; i < BRANCHES; i++)
        count += branchManagement->number_sales[i];

    return count;
}


void getClientsOfAllBranchesHelper(BranchManagement branchManagement, char** clients, int* isOnBranches, int number_clients) {
    for(int i = 0; i < number_clients; i++)
        for(int j = 0; j < BRANCHES; j++)
            if(!isOnBranch(branchManagement->branches[j], clients[i])) {
                isOnBranches[i] = 0;
                break;
            }
}


void getProductsStatsBoughtByClientHelper(BranchManagement branchManagement, char* id, int* content) {
    for(int i = 0; i < BRANCHES; i++) 
        getProductsStatsBoughtByClientOnBranch(branchManagement->branches[i], i + 1, id, content);
}
 

int getClientThatNeverBoughtCount(BranchManagement branchManagement) {
    int count = 0;

    for(int i = 0; i < BRANCHES; i++) 
        getClientThatNeverBoughtCountOnBranch(branchManagement->branches[i], &count);

    return count;
}