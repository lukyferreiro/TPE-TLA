#include <stdio.h>
#include <stdlib.h>
#include "bst_tree.h"

static struct node* newBstNode(int key) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->type = BST;
    temp->color=NONE;
    return temp;
}

struct node* insertBstNode(struct node* node, int key) {
    if (node == NULL)
        return newBstNode(key);

    if (key < node->key)
        node->left = insertBstNode(node->left, key);
    else if (key > node->key)
        node->right = insertBstNode(node->right, key);

    return node;
}

struct node* deleteBstNode(struct node* node, int key) {
    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = deleteBstNode(node->left, key);
    else if (key > node->key)
        node->right = deleteBstNode(node->right, key);

    else {
        if (node->left == NULL) {
            struct node* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct node* temp = node->left;
            free(node);
            return temp;
        }

        struct node* temp = minValueNode(node->right);

        node->key = temp->key;

        node->right = deleteBstNode(node->right, temp->key);
    }
    return node;
}