#ifndef TREE_H
#define TREE_H

#include "../semantic-analysis/abstract-syntax-tree.h"
#include <stdio.h>

#define LEGEND_TYPES 5

typedef enum rbtTypeEnum {
    RED,
    BLACK,
    NO_COLOR
} rbtTypeEnum;

struct node {
    TreeType type;
    int key;
    int found;
    struct node *left, *right;

    // Para avl
    int height;

    // Para rbt
    struct node* par;
    rbtTypeEnum color;

    // Para dot
    int dotNumber;
};

// General tree functions
struct node* insertFirstNode(struct node* node, int key, TreeType type, int* flag);
struct node* insertNode(struct node* node, int key, int* flag);
struct node* deleteNode(struct node* node, int key, int* flag);
void findNode(struct node* node, int key);
void resetFindNode(struct node* node);
struct node* switchType(struct node* node, TreeType type, int* flag);
void generateDotFile(struct node** currentTrees, char** treeNames, int treeSize, LegendType* legend, FILE* out);
void freeTree(struct node* node);

// To be used in legend
struct node* minValueNode(struct node* node);
struct node* maxValueNode(struct node* node);
int nodeCount(struct node* node);
int treeHeight(struct node* node);
int isBalanced(struct node* node);

#endif