#include "rbt.h"

enum nodeColor {
	RED,
	BLACK
};

struct rbNode {
	char* data;
	int color;
	Node link[2];
};


// Create a red-black tree
static Node createNode(char* data) {
	Node newnode = (Node) malloc(sizeof(struct rbNode));

	data[strcspn(data, "\r\n")] = 0;

	newnode->data = strdup(data);
	newnode->color = RED;
	newnode->link[0] = newnode->link[1] = NULL;
	
	return newnode;
}

// Insert an node
void insertion(Node* root, char* data) {
	Node stack[98], ptr, newnode, xPtr, yPtr;
	int dir[98], ht = 0, index;
	ptr = *root;

	if(!(*root)) {
		*root = createNode(data);
		return;
	}

	stack[ht] = *root;
	dir[ht++] = 0;

	while(ptr) {
		if(strcmp(ptr->data, data) == 0)
			return;

		index = strcmp(ptr->data, data) > 0 ? 1 : 0;
		stack[ht] = ptr;
		ptr = ptr->link[index];
		dir[ht++] = index;
	}

	stack[ht - 1]->link[index] = createNode(data);

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


int lookup(Node root, char* data) {
    if(!root)
    	return 0;

	if(strcmp(root->data, data) == 0)
		return 1;

    if(strcmp(root->data, data) > 0)
      return lookup(root->link[1], data);

    return lookup(root->link[0], data);
}