#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef RBT_H
#define RBT_H

typedef struct rbNode* Node;

void insertion(Node* root, char* data);

int lookup(Node root, char* data);

#endif