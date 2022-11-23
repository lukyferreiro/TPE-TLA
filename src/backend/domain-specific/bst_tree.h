#ifndef BST_TREE_H
#define BST_TREE_H

#include "tree.h"

struct node* insertBstNode(struct node* node, int key, int* flag);
struct node* deleteBstNode(struct node* node, int key, int* flag);

#endif  