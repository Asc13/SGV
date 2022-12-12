#include "faturation.h"

struct faturation {
    double* fatByBranchAndMonth;
    int* salesByBranchAndMonth;
    int* neverBought;
};

/*
    N: Branch 1: 0-11      Branch 2: 12-23      Branch 3: 24-35 
    P: Branch 1: 36-47      Branch 2: 48-59      Branch 3: 60-71 

    mode: N -> 0   P -> 1
    code: (mode * BRANCHES * MONTHS) + (branch - 1) * MONTHS - 1 + month
*/

Faturation initFaturation() {
    int FULLTAM = MODES * BRANCHES * MONTHS;

    Faturation faturation = (Faturation) malloc(sizeof(struct faturation));
    faturation->fatByBranchAndMonth = (double*) malloc(FULLTAM * sizeof(double));
    faturation->salesByBranchAndMonth = (int*) malloc(FULLTAM * sizeof(int));
    faturation->neverBought = (int*) malloc(BRANCHES * sizeof(int));

    for(int i = 0; i < FULLTAM; i++) {
        faturation->fatByBranchAndMonth[i] = 0.0;
        faturation->salesByBranchAndMonth[i] = 0;

        if(i < BRANCHES)
            faturation->neverBought[i] = 1;
    }
    
    return faturation;
}


void addFaturation(Faturation faturation, int branch, int month, double price, int quantity, char mode) {
    int index = ((mode == 'N' ? 0 : 1) * BRANCHES * MONTHS) + (branch - 1) * MONTHS - 1 + month;

    faturation->fatByBranchAndMonth[index] += (double) price * quantity;
    faturation->salesByBranchAndMonth[index]++;

    if(faturation->neverBought[branch - 1] == 1)
        faturation->neverBought[branch - 1] = 0;
}


int neverBought(Faturation faturation, int branch) {
    if(branch == 0)
        return faturation->neverBought[0] &&
               faturation->neverBought[1] &&
               faturation->neverBought[2];
    else
        return faturation->neverBought[branch - 1];
}


void updateWithStatsByMonth(Faturation faturation, int minMonth, int maxMonth, int* count, double* fat) {
    int index = 0, gap = MONTHS * BRANCHES;

    for(int m = minMonth - 1; m < maxMonth; m++)
        for(int b = 0; b < BRANCHES; b++) {
            index = b * MONTHS + m;

            *fat += faturation->fatByBranchAndMonth[index] +
                    faturation->fatByBranchAndMonth[index + gap];

            *count += faturation->salesByBranchAndMonth[index] +
                      faturation->salesByBranchAndMonth[index + gap];
        }
}

