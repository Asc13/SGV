#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <omp.h>

#ifndef RBT_H
#define RBT_H

typedef struct rbNode* Node;

void insertion(Node* root, char* data, void* object);

int lookup(Node root, char* data);

void* lookupGet(Node root, char* data);

void getAll(Node root, char* content);

void getAllSeparated(Node root, char** content, int* index);

char** lookupGetAllNeverBought(Node root, int branch, int* count);

void lookupGetAllNeverBoughtCount(Node root, int* count);

void lookupGetProductsStatsBoughtByClient(Node root, int branch, char* key, int* content);

void lookupGetClientsThatNeverBought(Node root, int* count);

void lookupGetAllStats(Node root, int minMonth, int maxMonth, int* count, double* fat);

#endif