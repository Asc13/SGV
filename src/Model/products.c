#include "products.h"
#include "rbt.h"


struct products {
    Node* idsByFirstLetters;
    int num_values;
};



Products initProducts() {
    int FULLTAM = TAM * TAM;
    Products products = (Products) malloc(sizeof(struct products));
    products->idsByFirstLetters = (Node*) malloc(FULLTAM * sizeof(Node));
    products->num_values = 0;

    for(int i = 0; i < FULLTAM; i++)
        products->idsByFirstLetters[i] = NULL;

    return products;
}


void addProduct(Products products, char* id) {
    int first_index = (int) id[0] - ASCII,
        second_index = (int) id[1] - ASCII,
        index = TAM * first_index + second_index;

    insertion(&(products->idsByFirstLetters[index]), id, NULL);
    products->num_values++;
}


int searchProduct(Products products, char* id) {
    int first_index = (int) id[0] - ASCII,
        second_index = (int) id[1] - ASCII,
        index = TAM * first_index + second_index;

    return lookup(products->idsByFirstLetters[index], id);
}


int getNumProducts(Products products) {
    return products->num_values;    
}


char** getProductsStartedByLetterHelper(Products products, int* counter, char letter) {
    char** c = (char**) malloc(products->num_values * sizeof(char*));

    int index = ((int) letter - ASCII) * TAM;

    for(int i = 0; i < TAM; i++) {
        getAllSeparated(products->idsByFirstLetters[index + i], c, counter);
    }

    c = (char**) realloc(c, *counter * sizeof(char*));

    return c;
}