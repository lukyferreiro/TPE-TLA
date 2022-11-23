#include <stdio.h>
#include <stdlib.h>
#include "bst_tree.h"
#include "../../backend/support/logger.h"

static struct node* newBstNode(int key, int *flag) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
    if(temp==NULL){
        (*flag)=2;
        LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
        return NULL;
    }
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->type = BST_TYPE;
    temp->color=NONE;
    return temp;
}

struct node* insertBstNode(struct node* node, int key, int *flag) {
    if (node == NULL)
        return newBstNode(key, flag);

    if (key < node->key)
        node->left = insertBstNode(node->left, key, flag);
    else if (key > node->key)
        node->right = insertBstNode(node->right, key, flag);
    else if (key == node->key){
        (*flag)=*flag == 0 ? 1: *flag;
        LogWarn("No se pudo agregar. El nodo %d ya se encontraba en el árbol", key);
    }
    return node;
}

struct node* deleteBstNode(struct node* node, int key, int* flag) {
    if (node == NULL){
        (*flag)=*flag == 0 ? 1: *flag;
        LogWarn("No se pudo eliminar. El nodo %d no se encontraba en el árbol", key);
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