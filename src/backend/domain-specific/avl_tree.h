#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "tree.h"

struct node* insertAvlNode(struct node* node, int key, int* flag);
struct node* deleteAvlNode(struct node* node, int key, int* flag);

#endif 