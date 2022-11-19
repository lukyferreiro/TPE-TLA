#ifndef TREE_H
#define TREE_H

typedef enum treeTypeEnum {
    BST,
    AVL,
    RBT
} treeTypeEnum;

typedef enum rbtTypeEnum {
    RED,
    BLACK,
    NONE
} rbtTypeEnum;

struct node {
    treeTypeEnum type;
    int key;
    int found;
    struct node *left, *right;

    // Para avl
    int height;

    // Para rbt
    struct node* par;
    rbtTypeEnum color;
};

// General tree functions
struct node* insertFirstNode(struct node* node, int key, treeTypeEnum type);
struct node* insertNode(struct node* node, int key);
struct node* deleteNode(struct node* node, int key);
void findNode(struct node* node, int key);
struct node* switchType(struct node* node, treeTypeEnum type);
void generateDot(struct node* node);
void freeTree(struct node* node);

//To be used in legend
struct node* minValueNode(struct node* node);
struct node* maxValueNode(struct node* node);
int nodeCount(struct node* node);
int treeHeight(struct node* node);
int isBalanced(struct node* node);

#endif