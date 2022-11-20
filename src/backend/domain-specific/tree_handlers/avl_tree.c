#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

static int height(struct node* node);
static int max(int a, int b);
static struct node* newAvlNode(int key);
static struct node* rightRotate(struct node* y);
static struct node* leftRotate(struct node* x);
static int getBalance(struct node* node);

int height(struct node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static struct node* newAvlNode(int key) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    temp->type = AVL_TYPE;
    temp->color=NONE;
    return temp;
}

static struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int getBalance(struct node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct node* insertAvlNode(struct node* node, int key) {
    if (node == NULL)
        return (newAvlNode(key));

    if (key < node->key)
        node->left = insertAvlNode(node->left, key);
    else if (key > node->key)
        node->right = insertAvlNode(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct node* deleteAvlNode(struct node* node, int key) {
    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = deleteAvlNode(node->left, key);

    else if (key > node->key)
        node->right = deleteAvlNode(node->right, key);

    else {
        if ((node->left == NULL) || (node->right == NULL)) {
            struct node* temp = node->left ? node->left : node->right;

            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;
            free(temp);
        } else {
            struct node* temp = minValueNode(node->right);

            node->key = temp->key;

            node->right = deleteAvlNode(node->right, temp->key);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}