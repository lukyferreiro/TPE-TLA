#include "tree.h"
#include "../../backend/support/logger.h"
#include "avl_tree.h"
#include "bst_tree.h"
#include "rbt_tree.h"
#include <stdio.h>
#include <stdlib.h>

static int max(int a, int b);
static void transformToBst(struct node* node);
static struct node* transformToAvl(struct node* node, int* flag);
static struct node* transformToRbt(struct node* node, int* flag);
static int* transformTreeToArray(struct node* node, int* size);
static int addToArray(struct node* node, int arr[], int i);
static void assignDotNumber(struct node* node, int* i);
static void generateDotSubGraph(struct node* node, char* treeName, int* i, int clusternum, LegendType* legend, FILE* out);
static void generateDot(struct node* node, FILE* out);
static void handleFlagWarning(int flag);

struct node* insertFirstNode(struct node* node, int key, TreeType type, int* flag) {
    switch (type) {
        case BST_TYPE:
            node = insertBstNode(node, key, flag);
            break;
        case AVL_TYPE:
            node = insertAvlNode(node, key, flag);
            break;
        case RBT_TYPE:
            node = insertRbtNode(node, key, flag);
            break;
        default:
            return NULL;
    }
    return node;
}

struct node* insertNode(struct node* node, int key, int* flag) {
    switch (node->type) {
        case BST_TYPE:
            node = insertBstNode(node, key, flag);
            break;
        case AVL_TYPE:
            node = insertAvlNode(node, key, flag);
            break;
        case RBT_TYPE:
            node = insertRbtNode(node, key, flag);
            break;
        default:
            return NULL;
    }
    return node;
}

struct node* deleteNode(struct node* node, int key, int* flag) {
    if (node == NULL) {
        (*flag) = 1;
        return NULL;
    }

    switch (node->type) {
        case BST_TYPE:
            node = deleteBstNode(node, key, flag);
            break;
        case AVL_TYPE:
            node = deleteAvlNode(node, key, flag);
            break;
        case RBT_TYPE:
            LogWarn("La operación de borrado no se encuentra disponible para arboles rbt aun");
            // node = deleteRbtNode(node, key, &flag);
            break;
        default:
            return NULL;
    }

    return node;
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

void resetFindNode(struct node* node) {
    if (node != NULL) {
        node->found = 0;
        resetFindNode(node->left);
        resetFindNode(node->right);
    }
}

struct node* switchType(struct node* node, TreeType type, int* flag) {
    if (node == NULL || node->type == type) {
        return node;
    }

    switch (type) {
        case BST_TYPE:
            transformToBst(node);
            return node;

        case AVL_TYPE:
            return transformToAvl(node, flag);

        case RBT_TYPE:
            return transformToRbt(node, flag);

        default:
            return node;
    }
}

void generateDotFile(struct node** currentTrees, char** treeNames, int treeSize, LegendType* legend, FILE* out) {
    fprintf(out, "strict digraph{ ");

    int i = 0;

    for (int x = 0; x < treeSize; x++) {
        generateDotSubGraph(currentTrees[x], treeNames[x], &i, x, legend, out);
    }

    fprintf(out, "}");
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
        node->color = NO_COLOR;
        node->type = BST_TYPE;
        transformToBst(node->left);
        transformToBst(node->right);
    }
}

static struct node* transformToAvl(struct node* node, int* flag) {
    int i;
    int* allNodes = transformTreeToArray(node, &i);

    if (allNodes == NULL) {
        (*flag) = 2;
        return NULL;
    }

    struct node* toRet = NULL;

    for (int j = 0; j < i; j++) {
        toRet = insertFirstNode(toRet, allNodes[j], AVL_TYPE, flag);
    }

    free(allNodes);
    freeTree(node);

    return toRet;
}

static struct node* transformToRbt(struct node* node, int* flag) {
    int i;
    int* allNodes = transformTreeToArray(node, &i);

    if (allNodes == NULL) {
        (*flag) = 2;
        return NULL;
    }

    struct node* toRet = NULL;

    for (int j = 0; j < i; j++) {
        toRet = insertFirstNode(toRet, allNodes[j], RBT_TYPE, flag);
    }

    free(allNodes);
    freeTree(node);

    return toRet;
}

static int* transformTreeToArray(struct node* node, int* size) {
    int count = nodeCount(node);
    int i = 0;
    int* allNodes = malloc(count * sizeof(int));

    if (allNodes == NULL) {
        return allNodes;
    }

    i = addToArray(node, allNodes, i);

    *size = i;

    return allNodes;
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

static void assignDotNumber(struct node* node, int* i) {
    if (node != NULL) {
        assignDotNumber(node->left, i);
        node->dotNumber = *i;
        (*i)++;
        assignDotNumber(node->right, i);
    }
}

static void generateDotSubGraph(struct node* node, char* treeName, int* i, int clusternum, LegendType* legend, FILE* out) {
    assignDotNumber(node, i);
    // asignar numero de cluster para que se imprima aparte
    fprintf(out, "\nsubgraph cluster%d{ \n", clusternum);
    struct node* aux;

    fprintf(out, "\tlabel=\"%s \\n", treeName);
    for (int x = 0; x < LEGEND_TYPES; x++) {
        switch (legend[x]) {
            case MAX_LEGEND:
                aux = maxValueNode(node);
                fprintf(out, "Maximo valor: %d\\n", aux->key);
                break;

            case MIN_LEGEND:
                aux = minValueNode(node);
                fprintf(out, "Minimo valor: %d\\n", aux->key);
                break;

            case COUNT_LEGEND:
                fprintf(out, "Cantidad de nodos: %d\\n", nodeCount(node));
                break;

            case BALANCED_LEGEND:
                if (isBalanced(node)) {
                    fprintf(out, "Arbol balanceado\\n");
                } else {
                    fprintf(out, "Arbol no balanceado\\n");
                }
                break;

            case HEIGHT_LEGEND:
                fprintf(out, "Altura del arbol: %d\\n", treeHeight(node) - 1);
                break;

            default:
                break;
        }
    }
    fprintf(out, "\";\n");
    generateDot(node, out);
    fprintf(out, "}\n");
}

static void generateDot(struct node* node, FILE* out) {
    if (node != NULL) {
        if (node->found) {
            if (node->color == RED) {
                fprintf(out, "\tn%d [style=\"filled, setlinewidth(2)\" color=\"red\" fillcolor=\"greenyellow\"] ;\n", node->dotNumber);
            } else if (node->color == BLACK) {
                fprintf(out, "\tn%d [style=\"filled, setlinewidth(2)\" color=\"black\" fillcolor=\"greenyellow\"] ;\n", node->dotNumber);
            } else {
                fprintf(out, "\tn%d [color=\"greenyellow\" style=\"filled\"] ;\n", node->dotNumber);
            }
        } else if (node->color == RED) {
            fprintf(out, "\tn%d [color=\"red\"] ;\n", node->dotNumber);
        } else if (node->color == BLACK) {
            fprintf(out, "\tn%d [color=\"black\"] ;\n", node->dotNumber);
        }

        fprintf(out, "\tn%d [label=\"%d\"] ;\n", node->dotNumber, node->key);
        if (node->left != NULL) {
            fprintf(out, "\tn%d->n%d ;\n", node->dotNumber, node->left->dotNumber);
        }
        if (node->right != NULL) {
            fprintf(out, "\tn%d->n%d ;\n", node->dotNumber, node->right->dotNumber);
        }

        generateDot(node->left, out);
        generateDot(node->right, out);
    }
}
