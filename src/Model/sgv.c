#include "sgv.h"
#include "clients.h"
#include "products.h"
#include "globalFaturation.h"
#include "branchManagement.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


struct sgv {
    Clients clients;
    Products products;
    GlobalFaturation globalFaturation;
    BranchManagement branchManagement;
};



static void validateToken(SGV sgv, char* token, int flag, int index, int* rc) {
    switch(index) {
        case 0:
            // product code
            *rc = isupper(token[0]) && isupper(token[1]) && atoi(token + 2) >= 1000 && atoi(token + 2) <= 9999;

            if(flag == 1 && *rc)
                addProduct(sgv->products, token);

            if(flag == 2 && *rc)
                *rc = searchProduct(sgv->products, token);

            break;

        case 1:
            double price = atof(token);
            *rc = price >= 0.0 && price <= 999.99;
            break;

        case 2:
            int quantity = atoi(token);
            *rc = quantity >= 0 && quantity <= 200;
            break;
        
        case 3:
            *rc = token[0] == 'P' || token[0] == 'N';
            break;

        case 4:
            // client code
            *rc = isupper(token[0]) && atoi(token + 1) >= 1000 && atoi(token + 1) <= 5000;

            if(flag == 0 && *rc)
                addClient(sgv->clients, token);

            if(flag == 2 && *rc)
                *rc = searchClient(sgv->clients, token);

            break;

        case 5:
            int month = atoi(token); 
            *rc = month >= 0 && month <= 12;
            break;

        case 6:
            int branch = atoi(token);
            *rc = branch >= 0 && branch <= 3;

            if(flag == 2 && *rc) {
                //addFaturationElement(sgv->globalFaturation);
                //addBranchElement(sgv->branchManagement, branch);
            }
            break;
    
        default:
            break;
    }
}


static void splitAndValidate(SGV sgv, char* line, int flag, int* rc) {
    int c = 0;
    char *start = &line[0];
    char sep = ' ';

    for(char* iter = start; *iter != '\0'; ++iter) {
        if(*iter == sep) {
            *iter = '\0';

            validateToken(sgv, start, flag, c, rc);

            if(!(*rc))
                break;
            
            start = iter + 1;
            c++;
        }
    }
}


static void readAndValidateFile(SGV sgv, FILE* fp, int flag) {
    char line[32];

    int v = 0, all = 0;
    int rc = 1;

    while(fgets(line, sizeof(line), fp)) {
        switch(flag) {
            case 0:
                validateToken(sgv, line, flag, 4, &rc);
                break;

            case 1:
                validateToken(sgv, line, flag, 0, &rc);
                break;

            case 2:
                splitAndValidate(sgv, line, flag, &rc);
                break;

            default:
                break;
        }

        if(rc > 0)
            v++;

        all++;
        rc = 1;
    }

    printf("\nValid = %d\nAll = %d\n", v, all);
}


SGV initSGV() {
    SGV sgv = (SGV) malloc(sizeof(struct sgv));

    sgv->clients = initClients();
    sgv->products = initProducts();

    return sgv;
}

void destroySGV(SGV sgv) {

}

SGV loadSGVFromFiles(SGV sgv, char* clientsFilePath, char* productsFilePath, char* salesFilePath) {
    FILE *c = fopen(clientsFilePath, "r");
    FILE *p = fopen(productsFilePath, "r");
    FILE *s = fopen(salesFilePath, "r");

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    
    readAndValidateFile(sgv, c, 0);
    readAndValidateFile(sgv, p, 1);
    readAndValidateFile(sgv, s, 2);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed Time: %f\n", cpu_time_used);

    fclose(c);
    fclose(p);
    fclose(s);
    return sgv;
}

void getCurrentFileInfo(SGV sgv) {

}

void getProductsStartedByLetter(SGV sgv, char letter) {
    
}

void getProductSalesAndProfit(SGV sgv, char* productID, int month) {

}

void getProductsNeverBought(SGV sgv, int branch) {

}

void getClientsOfAllBranches(SGV sgv) {

}

void getClientsAndProductsNeverBoughtCount(SGV sgv) {

}

void getProductsBoughtByClient(SGV sgv, char* clientID) {

}

void getSalesAndProfit(SGV sgv, int minMonth, int maxMonth) {

}

void getProductsBuyers(SGV sgv, char* productID, int branch) {

}

void getClientFavoriteProducts(SGV sgv, char* clientID, int month) {

}

void getTopSelledProducts(SGV sgv, int limit) {

}

void getClientTopProfitProducts(SGV sgv, char* clientID, int limit) {

}