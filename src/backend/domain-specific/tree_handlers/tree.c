#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "bst_tree.h"
#include "avl_tree.h"
#include "rbt_tree.h"

struct node* minValueNode(struct node* node) {
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
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

void generateDotFile(struct node* node) {
    printf("strict digraph{ \n");
    generateDot(node);
    printf("}");
}

struct node* insertFirstNode(struct node* node, int key, treeTypeEnum type){
    switch (type) {
        case BST:
            return insertBstNode(node, key);
        case AVL:
            return insertAvlNode(node, key);
        case RBT:
            //return insertRbtNode(node, key);
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
            //return insertRbtNode(node, key);
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
            //return deleteRbtNode(node, key);
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

void freeTree(struct node* node) {
    if (node!=NULL) {
		freeTree(node->left);
		freeTree(node->right);
		free(node);
	}
}

static void transformToBst(struct node* node){
    if (node!=NULL){
        node->height=0;
        node->par=NULL;
        node->color=NONE;
        node->type=BST;
        transformToBst(node->left);
        transformToBst(node->right);
    }
}

static struct node* transformToAvl(struct node* node, struct node* toRet){
    //check como insertar recursivamente los nodos de un arbol a otro de otro tipo
}

struct node* switchType(struct node* node, treeTypeEnum type){
    struct node* toRet = node;

    if(node->type==type){
        return toRet;
    }

    switch (type)
    {
    case BST:
        transformToBst(node);
        return toRet;
    
    case AVL:
    //check how to do
        return toRet;

    case RBT:

        break;
    
    default:
        break;
    }
}
