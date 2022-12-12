#include "sale.h"


struct sale {
    int month;
    double price;
    int quantity;
    char mode;
};


Sale initSale(int month, double price, int quantity, char mode) {
    Sale sale = (Sale) malloc(sizeof(struct sale));

    sale->month = month;
    sale->price = price;
    sale->quantity = quantity;
    sale->mode = mode;
    
    return sale;
}


void updateWithSaleMonthAndQuantity(Sale sale, int branch, int* content) {
    content[(branch - 1) * MONTHS + sale->month - 1] += sale->quantity;
}