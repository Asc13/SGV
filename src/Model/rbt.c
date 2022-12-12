#include "rbt.h"
#include "faturation.h"
#include "branchEntry.h"


enum nodeColor {
	RED,
	BLACK
};

struct rbNode {
	char* key;
	void* object;
	int color;
	Node link[2];
};



static Node createNode(char* key, void* object) {
	Node newnode = (Node) malloc(sizeof(struct rbNode));

	newnode->object = object;
	newnode->key = strdup(key);
	newnode->color = RED;
	newnode->link[0] = newnode->link[1] = NULL;
	
	return newnode;
}


void insertion(Node* root, char* key, void* object) {
	Node stack[98], ptr, newnode, xPtr, yPtr;
	int dir[98], ht = 0, index;
	ptr = *root;

	key[strcspn(key, "\r\n")] = 0;

	if(!(*root)) {
		*root = createNode(key, object);
		return;
	}

	stack[ht] = *root;
	dir[ht++] = 0;

	while(ptr) {
		if(strcmp(key, ptr->key) == 0)
			return;

		index = strcmp(key, ptr->key) > 0 ? 1 : 0;
		stack[ht] = ptr;
		ptr = ptr->link[index];
		dir[ht++] = index;
	}

	stack[ht - 1]->link[index] = createNode(key, object);

	while((ht >= 3) && (stack[ht - 1]->color == RED)) {

		if(dir[ht - 2] == 0) {
			yPtr = stack[ht - 2]->link[1];

			if(yPtr != NULL && yPtr->color == RED) {
				stack[ht - 2]->color = RED;
				stack[ht - 1]->color = yPtr->color = BLACK;
				ht = ht - 2;
			} 
			else {
				if (dir[ht - 1] == 0)
					yPtr = stack[ht - 1];

				else {
					xPtr = stack[ht - 1];
					yPtr = xPtr->link[1];
					xPtr->link[1] = yPtr->link[0];
					yPtr->link[0] = xPtr;
					stack[ht - 2]->link[0] = yPtr;
				}

				xPtr = stack[ht - 2];
				xPtr->color = RED;
				yPtr->color = BLACK;
				xPtr->link[0] = yPtr->link[1];
				yPtr->link[1] = xPtr;
				
				if(xPtr == *root)
					*root = yPtr;
				
				else
					stack[ht - 3]->link[dir[ht - 3]] = yPtr;

				break;
			}
		} 
		else {
			yPtr = stack[ht - 2]->link[0];

			if((yPtr != NULL) && (yPtr->color == RED)) {
				stack[ht - 2]->color = RED;
				stack[ht - 1]->color = yPtr->color = BLACK;
				ht = ht - 2;
			} 
			else {
				if(dir[ht - 1] == 1)
					yPtr = stack[ht - 1];
				
				else {
					xPtr = stack[ht - 1];
					yPtr = xPtr->link[0];
					xPtr->link[0] = yPtr->link[1];
					yPtr->link[1] = xPtr;
					stack[ht - 2]->link[1] = yPtr;
				}

				xPtr = stack[ht - 2];
				yPtr->color = BLACK;
				xPtr->color = RED;
				xPtr->link[1] = yPtr->link[0];
				yPtr->link[0] = xPtr;
				
				if(xPtr == *root)
					*root = yPtr;

				else
					stack[ht - 3]->link[dir[ht - 3]] = yPtr;

				break;
			}
		}
	}
	(*root)->color = BLACK;
}


int lookup(Node root, char* key) {
    if(!root)
    	return 0;

	if(strcmp(key, root->key) == 0)
		return 1;

    if(strcmp(key, root->key) > 0)
      	return lookup(root->link[1], key);

    return lookup(root->link[0], key);
}


void* lookupGet(Node root, char* key) {
    if(!root)
    	return NULL;

	if(strcmp(key, root->key) == 0)
		return root->object;

    if(strcmp(key, root->key) > 0)
      	return lookupGet(root->link[1], key);

    return lookupGet(root->link[0], key);
}


void getAll(Node root, char* content) {
    if(root) {
		getAll(root->link[0], content);

		strcat(strcat(content, "\n"), root->key);

		getAll(root->link[1], content);
	}
}


void getAllSeparated(Node root, char** content, int* index) {
    if(root) {
		getAllSeparated(root->link[0], content, index);

		content[(*index)++] = strdup(root->key);

		getAllSeparated(root->link[1], content, index);
	}
}


static void lookupGetAllNeverBoughtHelper(Node root, int branch, char*** content, int *dynamic_size, int* count) {
	if(root) {
		lookupGetAllNeverBoughtHelper(root->link[0], branch, content, dynamic_size, count);

		if(neverBought((Faturation) root->object, branch)) {
			if(*count == *dynamic_size) {
				*dynamic_size *= 2;
				*content = (char**) realloc(*content, *dynamic_size * sizeof(char*));
			}

			(*content)[(*count)++] = strdup(root->key);
			
		}

		lookupGetAllNeverBoughtHelper(root->link[1], branch, content, dynamic_size, count);
	}
}


char** lookupGetAllNeverBought(Node root, int branch, int* count) {
	char** dynamicContent = NULL;

	if(root) {
		int dynamic_size = 10;
		dynamicContent = (char**) malloc(dynamic_size * sizeof(char*));

		lookupGetAllNeverBoughtHelper(root, branch, &dynamicContent, &dynamic_size, count);

		dynamicContent = (char**) realloc(dynamicContent, *count * sizeof(char*));
	}

	return dynamicContent;
}


void lookupGetAllNeverBoughtCount(Node root, int* count) {
	if(root) {
		lookupGetAllNeverBoughtCount(root->link[0], count);

		if(neverBought((Faturation) root->object, 0))
			(*count)++;

		lookupGetAllNeverBoughtCount(root->link[1], count);
	}
}


void lookupGetProductsStatsBoughtByClient(Node root, int branch, char* key, int* content) {
	if(!root)
    	return;

	if(strcmp(key, root->key) == 0)
		getAllQuantitiesFromBranchEntryByBranch((BranchEntry) root->object, branch, content);

    if(strcmp(key, root->key) > 0)
      	lookupGetProductsStatsBoughtByClient(root->link[1], branch, key, content);

    lookupGetProductsStatsBoughtByClient(root->link[0], branch, key, content);
}


void lookupGetClientsThatNeverBought(Node root, int* count) {
	if(root) {
		lookupGetClientsThatNeverBought(root->link[0], count);

		if(getNumberCodes((BranchEntry) root->object) == 0)
			(*count)++;

		lookupGetClientsThatNeverBought(root->link[1], count);
	}
}


void lookupGetAllStats(Node root, int minMonth, int maxMonth, int* count, double* fat) {
	if(root) {
		lookupGetAllStats(root->link[0], minMonth, maxMonth, count, fat);

		updateWithStatsByMonth((Faturation) root->object, minMonth, maxMonth, count, fat);

		lookupGetAllStats(root->link[1], minMonth, maxMonth, count, fat);
	}
}