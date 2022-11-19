#ifndef RBT_TREE_H
#define RBT_TREE_H

#include "tree.h"

struct node* insertRbtNode(struct node* node, int key);
struct node* deleteRbtNode(struct node* node, int key);

#endif