#include "view.h"
#include <stdio.h>

void show(char* buffer) {
    printf("%s", buffer);
}


void showTable(int* table, int x, int y) {
    printf("\n         |");

    for(int b = 0; b < y; b++)
        printf(" Filial %3d |", b + 1);
    
    printf("\n---------|");

    for(int b = 0; b < y; b++) {
        printf("------------|");
    }

    printf("\n");

    for(int m = 0; m < x; m++) {
        printf("Month %2d |", m + 1);
        
        for(int b = 0; b < y; b++)
            printf(" %10d |", table[b * x + m]);

        printf("\n");
    }

    printf("\n");
}