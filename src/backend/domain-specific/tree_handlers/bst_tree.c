#include <stdio.h>
#include <stdlib.h>
#include "bst_tree.h"

static struct node* newBstNode(int key) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->type = BST_TYPE;
    temp->color=NONE;
    return temp;
}

struct node* insertBstNode(struct node* node, int key, int *flag) {
    if (node == NULL)
        return newBstNode(key);

    if (key < node->key)
        node->left = insertBstNode(node->left, key, flag);
    else if (key > node->key)
        node->right = insertBstNode(node->right, key, flag);
    else if (key == node->key){
        (*flag)=1;
    }
    return node;
}

struct node* deleteBstNode(struct node* node, int key, int* flag) {
    if (node == NULL){
        (*flag)=3;
        return node;
    }

    if (key < node->key)
        node->left = deleteBstNode(node->left, key, flag);
    else if (key > node->key)
        node->right = deleteBstNode(node->right, key, flag);

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
        int aux=0;
        node->right = deleteBstNode(node->right, temp->key, &aux);
    }
    return node;
}