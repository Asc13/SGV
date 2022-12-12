#include "branchEntry.h"
#include "sale.h"


struct branchEntry {
    char** productsCodes;
    Sale* sales;
    int number_codes;
    int dynamic_size;
};



BranchEntry initBranchEntry() {
    BranchEntry branchEntry = (BranchEntry) malloc(sizeof(struct branchEntry));

    branchEntry->number_codes = 0;
    branchEntry->dynamic_size = 1;

    return branchEntry;
}


void updateSalesEntry(BranchEntry branchEntry, char* product, int month, double price, int quantity, char mode) {
    if(branchEntry->number_codes == 0) {
        branchEntry->productsCodes = (char**) malloc(sizeof(char*));
        branchEntry->sales = (Sale*) malloc(sizeof(Sale));
    }
    else if(branchEntry->number_codes == branchEntry->dynamic_size) {
        branchEntry->dynamic_size *= 2;
        branchEntry->productsCodes = (char**) realloc(branchEntry->productsCodes, branchEntry->dynamic_size * sizeof(char*));
        branchEntry->sales = (Sale*) realloc(branchEntry->sales, branchEntry->dynamic_size * sizeof(Sale));
    }

    branchEntry->productsCodes[branchEntry->number_codes] = strdup(product);
    branchEntry->sales[branchEntry->number_codes++] = initSale(month, price, quantity, mode);
}


void getAllQuantitiesFromBranchEntryByBranch(BranchEntry branchEntry, int branch, int* content) {
    for(int i = 0; i < branchEntry->number_codes; i++)
        updateWithSaleMonthAndQuantity(branchEntry->sales[i], branch, content);
}


int getNumberCodes(BranchEntry branchEntry) {
    return branchEntry->number_codes;
}