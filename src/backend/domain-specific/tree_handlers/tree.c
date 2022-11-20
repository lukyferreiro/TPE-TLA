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
static void assignDotNumber(struct node* node, int* i);
static int* transformTreeToArray(struct node* node, int* size);
static void generateDot(struct node* node);

struct node* insertFirstNode(struct node* node, int key, TreeType type) {
    switch (type) {
        case BST_TYPE:
            return insertBstNode(node, key);
        case AVL_TYPE:
            return insertAvlNode(node, key);
        case RBT_TYPE:
            // return insertRbtNode(node, key);
            return NULL;
        default:
            return NULL;
    }
}

struct node* insertNode(struct node* node, int key) {
    switch (node->type) {
        case BST_TYPE:
            return insertBstNode(node, key);
        case AVL_TYPE:
            return insertAvlNode(node, key);
        case RBT_TYPE:
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
        case BST_TYPE:
            return deleteBstNode(node, key);
        case AVL_TYPE:
            return deleteAvlNode(node, key);
        case RBT_TYPE:
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

struct node* switchType(struct node* node, TreeType type) {
    if (node==NULL || node->type == type) {
        return node;
    }

    switch (type) {
        case BST_TYPE:
            transformToBst(node);
            return node;

        case AVL_TYPE:
            return transformToAvl(node);

        case RBT_TYPE:
            return node;

        default:
            return node;
    }
}

static void generateDot(struct node* node) {
    if (node != NULL) {
        if (node->found) {
            printf("\tn%d [color=\"greenyellow\" style=\"filled\"]\n", node->dotNumber);
        }

        printf("\tn%d [label=\"%d\"] ;\n", node->dotNumber, node->key);
        if (node->left != NULL) {
            printf("\tn%d->n%d;\n", node->dotNumber, node->left->dotNumber);
        }
        if (node->right != NULL) {
            printf("\tn%d->n%d;\n", node->dotNumber, node->right->dotNumber);
        }

        generateDot(node->left);
        generateDot(node->right);
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

static void assignDotNumber(struct node* node, int* i){
    if (node != NULL) {
        assignDotNumber(node->left, i);
        node->dotNumber=*i;
        (*i)++;
        assignDotNumber(node->right, i);
    }
}

void generateDotFile(struct node* node, int* i, int j, LegendType* legend, int legendSize) {
    assignDotNumber(node, i);
    // asignar numero de cluster para que se imprima aparte
    printf("\nsubgraph cluster%d{ \n", j);
    struct node* aux;

    printf("label=\" ");
    for(int x=0; x<legendSize; x++){
        switch (legend[x])
        {
        case MAX_LEGEND:
            aux=maxValueNode(node);
            printf("Maximo valor: %d\\n", aux->key);
            break;
        
        case MIN_LEGEND:
            aux=minValueNode(node);
            printf("Minimo valor: %d\\n", aux->key);
            break;
        
        case COUNT_LEGEND:
            printf("Cantidad de nodos: %d\\n", nodeCount(node));
            break;

        case BALANCED_LEGEND:
            if(isBalanced(node)){
                printf("Arbol balanceado\\n");
            }
            else {
                printf("Arbol no balanceado\\n");

            }
            break;

        case HEIGHT_LEGEND:
            printf("Altura del arbol: %d\\n", treeHeight(node)-1);
            break;               

        default:
            break;
        }
    }
    printf("\";\n");
    generateDot(node);
    printf("}\n");
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
        node->type = BST_TYPE;
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

static int* transformTreeToArray(struct node* node, int* size) {
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