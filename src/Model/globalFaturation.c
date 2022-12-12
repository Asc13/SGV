#include "globalFaturation.h"
#include "faturation.h"
#include "rbt.h"


struct globalFaturation {
    Node* fatsByFirstLetters;
};


GlobalFaturation initGlobalFaturation() {
    int FULLTAM = TAM * TAM;

    GlobalFaturation globalFaturation = (GlobalFaturation) malloc(sizeof(struct globalFaturation));
    globalFaturation->fatsByFirstLetters = (Node*) malloc(FULLTAM * sizeof(Node));

    for(int i = 0; i < FULLTAM; i++)
        globalFaturation->fatsByFirstLetters[i] = NULL;

    return globalFaturation;
}


void addProductToGlobalFaturation(GlobalFaturation globalFaturation, char* id) {
    int first_index = (int) id[0] - ASCII,
        second_index = (int) id[1] - ASCII,
        index = TAM * first_index + second_index;

    insertion(&(globalFaturation->fatsByFirstLetters[index]), id, initFaturation());
}


void updateProductFat(GlobalFaturation globalFaturation, char* id, int branch, int month, double price, int quantity, char mode) {
    int first_index = (int) id[0] - ASCII,
        second_index = (int) id[1] - ASCII,
        index = TAM * first_index + second_index;

    addFaturation((Faturation) lookupGet(globalFaturation->fatsByFirstLetters[index], id), 
                  branch, month, price, quantity, mode);
}


char** getProductsNeverBoughtHelper(GlobalFaturation globalFaturation, int branch, int* count) {
    int FULLTAM = TAM * TAM;

    int auxCount = 0;
    char** token;
    char** content;
    int arith = 0;

    for(int i = 0; i < FULLTAM; i++) {
        token = lookupGetAllNeverBought(globalFaturation->fatsByFirstLetters[i], branch, &auxCount);

        arith = (*count + auxCount);
        
        if(arith != *count) {
            if(*count)
                content = (char**) realloc(content, arith * sizeof(char*));
            else
                content = (char**) malloc(arith * sizeof(char*)); 
        }

        for(int j = *count, k = 0; j < arith; j++, k++) {
            content[j] = strdup(token[k]);
            free(token[k]);
        }
        *count = arith;
        auxCount = 0;
    }

    if(*count)
        free(token);

    return content;
}


int getNeverBoughtProductCount(GlobalFaturation globalFaturation) {
    int count = 0;
    int FULLTAM = TAM * TAM;

    for(int i = 0; i < FULLTAM; i++)
        lookupGetAllNeverBoughtCount(globalFaturation->fatsByFirstLetters[i], &count);

    return count;
}


void getFatAndSalesByMonths(GlobalFaturation globalFaturation, int minMonth, int maxMonth, int* count, double* fat) {
    int FULLTAM = TAM * TAM;

    for(int i = 0; i < FULLTAM; i++)
        lookupGetAllStats(globalFaturation->fatsByFirstLetters[i], minMonth, maxMonth, count, fat);
}