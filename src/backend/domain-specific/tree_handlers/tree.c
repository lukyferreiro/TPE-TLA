#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "bst_tree.h"
#include "avl_tree.h"
#include "rbt_tree.h"

static int max(int a, int b);
static void transformToBst(struct node* node);
static struct node* transformToAvl(struct node* node) ;
static int addToArray(struct node* node, int arr[], int i);
int* transformTreeToArray(struct node* node, int* size);

struct node* insertFirstNode(struct node* node, int key, treeTypeEnum type) {
    switch (type) {
        case BST:
            return insertBstNode(node, key);
        case AVL:
            return insertAvlNode(node, key);
        case RBT:
            // return insertRbtNode(node, key);
            return NULL;
        default:
            return NULL;
    }
}

struct node* insertNode(struct node* node, int key) {
    switch (node->type) {
        case BST:
            return insertBstNode(node, key);
        case AVL:
            return insertAvlNode(node, key);
        case RBT:
            // return insertRbtNode(node, key);
            return NULL;
        default:
            return NULL;
    }
}

struct node* deleteNode(struct node* node, int key) {
    if (node == NULL) {
        return NULL;
    }

    switch (node->type) {
        case BST:
            return deleteBstNode(node, key);
        case AVL:
            return deleteAvlNode(node, key);
        case RBT:
            // return deleteRbtNode(node, key);
            return NULL;
        default:
            return NULL;
    }
}

void findNode(struct node* node, int key) {
    if (node != NULL) {
        if (key < node->key) {
            findNode(node->left, key);
        }

        if (key > node->key) {
            findNode(node->right, key);
        }

        if (key == node->key) {
            node->found = 1;
        }
    }
}

struct node* switchType(struct node* node, treeTypeEnum type) {
    if (node->type == type) {
        return node;
    }

    switch (type) {
        case BST:
            transformToBst(node);
            return node;

        case AVL:
            return transformToAvl(node);

        case RBT:

            break;

        default:
            break;
    }
}

void generateDot(struct node* node) {
    if (node != NULL) {
        if (node->found) {
            printf("%d [color=\"green\"]", node->key);
        }

        if (node->left != NULL) {

            printf("\t%d->%d;\n", node->key, node->left->key);
            generateDot(node->left);
        }
        if (node->right != NULL) {

            printf("\t%d->%d;\n", node->key, node->right->key);
            generateDot(node->right);
        }
    }
}

void freeTree(struct node* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node* maxValueNode(struct node* node) {
    struct node* current = node;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

int nodeCount(struct node* node) {
    int c = 1;

    if (node == NULL)
        return 0;
    else {
        c += nodeCount(node->left);
        c += nodeCount(node->right);
        return c;
    }
}

void generateDotFile(struct node* node) {
    printf("strict digraph{ \n");
    generateDot(node);
    printf("}");
}

int treeHeight(struct node* node) {
    if (node == NULL)
        return 0;

    return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

int isBalanced(struct node* root) {
    int lh;
    int rh;

    if (root == NULL)
        return 1;

    lh = treeHeight(root->left);
    rh = treeHeight(root->right);

    if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;

    return 0;
}

static int max(int a, int b) { return (a >= b) ? a : b; }

static void transformToBst(struct node* node) {
    if (node != NULL) {
        node->height = 0;
        node->par = NULL;
        node->color = NONE;
        node->type = BST;
        transformToBst(node->left);
        transformToBst(node->right);
    }
}

static int addToArray(struct node* node, int arr[], int i) {
    if (node == NULL)
        return i;

    arr[i] = node->key;
    i++;
    if (node->left != NULL)
        i = addToArray(node->left, arr, i);
    if (node->right != NULL)
        i = addToArray(node->right, arr, i);

    return i;
}

int* transformTreeToArray(struct node* node, int* size) {
    int count = nodeCount(node);
    int i = 0;
    int* allNodes = malloc(count * sizeof(int));
    i = addToArray(node, allNodes, i);

    *size = i;

    return allNodes;
}

static struct node* transformToAvl(struct node* node) {
    int i;
    int* allNodes = transformTreeToArray(node, &i);
    struct node* toRet = NULL;

    for (int j = 0; j < i; j++) {
        toRet = insertAvlNode(toRet, allNodes[j]);
    }

    free(allNodes);
    freeTree(node);

    return toRet;
}