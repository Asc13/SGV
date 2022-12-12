#include "view.h"
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



static void validateToken(SGV sgv, char* token, int flag, int index, int* rc, void** object) {
    switch(index) {
        case 0:
            // product code
            if(flag == 1) {
                *rc = isupper(token[0]) && isupper(token[1]) && atoi(token + 2) >= 1000 && atoi(token + 2) <= 9999;

                if(*rc) {
                    addProduct(sgv->products, token);
                    addProductToGlobalFaturation(sgv->globalFaturation, token);
                }
            }

            if(flag == 2) {
                *rc = searchProduct(sgv->products, token);
                object[index] = token;
            }

            break;

        case 1:
            double price = atof(token);
            *rc = price >= 0.0 && price <= 999.99;

            object[index] = &price;
            break;

        case 2:
            int quantity = atoi(token);
            *rc = quantity >= 0 && quantity <= 200;

            object[index] = &quantity;
            break;
        
        case 3:
            *rc = token[0] == 'P' || token[0] == 'N';

            object[index] = &(token[0]);     
            break;

        case 4:
            // client code
            if(flag == 0) {
                *rc = isupper(token[0]) && atoi(token + 1) >= 1000 && atoi(token + 1) <= 5000;

                if(*rc)
                    addClient(sgv->clients, token);
            }

            if(flag == 2) {
                *rc = searchClient(sgv->clients, token);
                object[index] = token;
            }

            break;

        case 5:
            int month = atoi(token); 
            *rc = month >= 0 && month <= 12;

            object[index] = &month;
            break;

        case 6:
            int branch = atoi(token);
            *rc = branch >= 0 && branch <= 3;

            if(flag == 2 && *rc) {
                updateProductFat(sgv->globalFaturation,
                                 object[0],
                                 branch,
                                 *((int*) object[5]),
                                 *((double*) object[1]),
                                 *((int*) object[2]),
                                 ((char*) object[3])[0]);
                                 
                addSaleToBranch(sgv->branchManagement, 
                                branch,
                                object[4],
                                object[0],
                                *((int*) object[5]),
                                *((double*) object[1]),
                                *((int*) object[2]),
                                ((char*) object[3])[0]);
            }
            break;
    
        default:
            break;
    }
}


static void splitAndValidate(SGV sgv, char* line, int flag, int* rc, void** object) {
    int c = 0;
    char *start = &line[0];
    char sep = ' ';

    for(char* iter = start; *iter != '\0'; ++iter) {
        if(*iter == sep) {
            *iter = '\0';

            validateToken(sgv, start, flag, c, rc, object);

            if(!(*rc))
                break;

            start = iter + 1;
            c++;
        }
    }

    if(*rc)
        validateToken(sgv, start, flag, 6, rc, object);
}


static void readAndValidateFile(SGV sgv, FILE* fp, int flag) {
    char line[32];
    int rc = 1;
    void** object;

    if(flag == 2)
        object = (void**) malloc(OBJECTSIZE * sizeof(void*));

    while(fgets(line, sizeof(line), fp)) {
        switch(flag) {
            case 0:
                validateToken(sgv, line, flag, 4, &rc, NULL);
                break;

            case 1:
                validateToken(sgv, line, flag, 0, &rc, NULL);
                break;

            case 2:
                splitAndValidate(sgv, line, flag, &rc, object);
                break;

            default:
                break;
        }

        rc = 1;
    }

    if(flag == 2)
        free(object);
}


SGV initSGV() {
    SGV sgv = (SGV) malloc(sizeof(struct sgv));

    sgv->clients = initClients();
    sgv->products = initProducts();
    sgv->globalFaturation = initGlobalFaturation();
    sgv->branchManagement = initBranchManagement();

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
    
    char time_string[50];
    sprintf(time_string, "\n\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);

    fclose(c);
    fclose(p);
    fclose(s);
    return sgv;
}

void getCurrentFileInfo(SGV sgv) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int validClients = getNumClients(sgv->clients);    
    int validProducts = getNumProducts(sgv->products);
    int validSales = getNumberSales(sgv->branchManagement);

    char resultString[100];
    sprintf(resultString, "\n\nValid clients: %d\nValid Products: %d\nValid sales: %d\n",
            validClients, validProducts, validSales);

    char time_string[50];
    sprintf(time_string, "\nElapsed Time: %f seconds\n\n", cpu_time_used);

    show(resultString);
    show(time_string);
}


void getProductsStartedByLetter(SGV sgv, char letter) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int counter = 0;
    char** products = getProductsStartedByLetterHelper(sgv->products, &counter, letter);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    for(int i = 0; i < counter; i++) {
        show(products[i]);
        show("\n");
        free(products[i]);
    }

    char time_string[50];
    sprintf(time_string, "\n\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);

    free(products);
}

void getProductSalesAndProfit(SGV sgv, char* productID, int month) {

}

void getProductsNeverBought(SGV sgv, int branch) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int count = 0;
    char** content = getProductsNeverBoughtHelper(sgv->globalFaturation, branch, &count);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    for(int i = 0; i < count; i++) {
        show(content[i]);
        show("\n");
        free(content[i]);
    }

    if(count)
        free(content);

    char countS[10];
    sprintf(countS, "\n\nCounter: %d\n", count);
    show(countS);

    char time_string[50];
    sprintf(time_string, "\n\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);

}

void getClientsOfAllBranches(SGV sgv) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int number_clients = getNumClients(sgv->clients);
    int* isOnBranches = (int*) malloc(number_clients * sizeof(int));

    for(int i = 0; i < number_clients; i++)
        isOnBranches[i] = 1;

    char** clients = getAllClients(sgv->clients);

    getClientsOfAllBranchesHelper(sgv->branchManagement, clients, isOnBranches, number_clients);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    for(int i = 0; i < number_clients; i++) {
        if(isOnBranches[i]) {
            show(clients[i]);
            show("\n");
        }

        free(clients[i]);
    }

    free(isOnBranches);
    free(clients);

    char countS[10];
    sprintf(countS, "\n\nCounter: %d\n", number_clients);
    show(countS);

    char time_string[50];
    sprintf(time_string, "\n\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);
}

void getClientsAndProductsNeverBoughtCount(SGV sgv) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int countC = getClientThatNeverBoughtCount(sgv->branchManagement),
        countP = getNeverBoughtProductCount(sgv->globalFaturation);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    char countS[50];
    sprintf(countS, "\n\nClients that never bought: %d\n", countC);
    show(countS);

    sprintf(countS, "\nProducts never bought: %d\n", countP);
    show(countS);

    char time_string[50];
    sprintf(time_string, "\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);
}

void getProductsBoughtByClient(SGV sgv, char* clientID) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int branches = 3;
    int months = 12;

    int* content = (int*) malloc(branches * months * sizeof(int));

    for(int i = 0; i < branches * months; i++)
        content[i] = 0;

    getProductsStatsBoughtByClientHelper(sgv->branchManagement, clientID, content);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    showTable(content, months, branches);

    free(content);

    char time_string[50];
    sprintf(time_string, "\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);
}

void getSalesAndProfit(SGV sgv, int minMonth, int maxMonth) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int count = 0;
    double fat = 0.0;
       
    getFatAndSalesByMonths(sgv->globalFaturation, minMonth, maxMonth, &count, &fat);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    char countS[50];
    sprintf(countS, "\n\nNumber of sales registed: %d\n", count);
    show(countS);

    sprintf(countS, "\nAmount invoiced: %f $\n", fat);
    show(countS);

    char time_string[50];
    sprintf(time_string, "\nElapsed Time: %f seconds\n\n", cpu_time_used);
    show(time_string);
}

void getProductsBuyers(SGV sgv, char* productID, int branch) {

}

void getClientFavoriteProducts(SGV sgv, char* clientID, int month) {

}

void getTopSelledProducts(SGV sgv, int limit) {

}

void getClientTopProfitProducts(SGV sgv, char* clientID, int limit) {

}