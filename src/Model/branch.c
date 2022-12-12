#include "branch.h"
#include "branchEntry.h"
#include "rbt.h"


struct branch {
    Node* clientsByFirstLetter;
};


Branch initBranch() {
    Branch branch = (Branch) malloc(sizeof(struct branch));

    branch->clientsByFirstLetter = (Node*) malloc(TAM * sizeof(Node));

    for(int i = 0; i < TAM; i++)
        (branch->clientsByFirstLetter)[i] = NULL;

    return branch;
}


void updateBranchEntry(Branch branch, char* id, char* product, int month, double price, int quantity, char mode) {
    int index = (int) id[0] - ASCII;

    BranchEntry branchEntry = (BranchEntry) lookupGet(branch->clientsByFirstLetter[index], id);

    if(!branchEntry) {
        BranchEntry newBranchEntry = initBranchEntry();
        insertion(&(branch->clientsByFirstLetter[index]), id, newBranchEntry);
        updateSalesEntry(newBranchEntry, product, month, price, quantity, mode);
    }
    
    else
        updateSalesEntry(branchEntry, product, month, price, quantity, mode);
}


int isOnBranch(Branch branch, char* id) {
    return lookup(branch->clientsByFirstLetter[(int) id[0] - ASCII], id);
}


void getProductsStatsBoughtByClientOnBranch(Branch branch, int branchID, char* id, int* content) {
    lookupGetProductsStatsBoughtByClient(branch->clientsByFirstLetter[(int) id[0] - ASCII], branchID, id, content);
}


void getClientThatNeverBoughtCountOnBranch(Branch branch, int* count) {
    for(int i = 0; i < TAM; i++)
        lookupGetClientsThatNeverBought(branch->clientsByFirstLetter[i], count);
}