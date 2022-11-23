#include "rbt_tree.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <stdlib.h>

static struct node* newRbtNode(int key, int* flag);
static struct node* bstInsertNode(struct node* trav, struct node* temp, int* flag);
static struct node* rightRotate(struct node* root, struct node* x);
static struct node* lefttrotate(struct node* root, struct node* x);
static struct node* fixup(struct node* root, struct node* pt);

static int alreadyAdded = 0;

struct node* insertRbtNode(struct node* node, int key, int* flag) {
    struct node* toAdd = newRbtNode(key, flag);
    if (toAdd == NULL) {
        return node;
    }
    node = bstInsertNode(node, toAdd, flag);
    if (alreadyAdded) {
        free(toAdd);
        alreadyAdded = 0;
        return node;
    }
    node = fixup(node, toAdd);
    return node;
}

static struct node* newRbtNode(int key, int* flag) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
    if (temp == NULL) {
        (*flag) = 2;
        LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
        return NULL;
    }
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->par = NULL;
    temp->type = RBT_TYPE;
    temp->color = RED;
    return temp;
}

struct node* bstInsertNode(struct node* trav, struct node* temp, int* flag) {
    if (trav == NULL)
        return temp;

    if (temp->key < trav->key) {
        trav->left = bstInsertNode(trav->left, temp, flag);
        trav->left->par = trav;
    } else if (temp->key > trav->key) {
        trav->right = bstInsertNode(trav->right, temp, flag);
        trav->right->par = trav;
    } else if (temp->key == trav->key) {
        (*flag) = *flag == 0 ? 1 : *flag;
        LogWarn("No se pudo agregar. El nodo %d ya se encontraba en el árbol", temp->key);
        alreadyAdded = 1;
    }

    return trav;
}

static struct node* rightRotate(struct node* root, struct node* x) {
    struct node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->par = x;
    y->par = x->par;
    if (x->par == NULL)
        root = y;
    else if (x == x->par->right)
        x->par->right = y;
    else
        x->par->left = y;
    y->right = x;
    x->par = y;
    return root;
}

struct node* leftRotate(struct node* root, struct node* x) {
    struct node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->par = x;
    y->par = x->par;
    if (x->par == NULL)
        root = y;
    else if (x == x->par->left)
        x->par->left = y;
    else
        x->par->right = y;
    y->left = x;
    x->par = y;

    return root;
}

static struct node* fixup(struct node* root, struct node* pt) {
    if (pt == NULL) {
        return root;
    }
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) && (pt->par->color == RED)) {
        parent_pt = pt->par;
        grand_parent_pt = pt->par->par;

        if (parent_pt == grand_parent_pt->left) {

            struct node* uncle_pt = grand_parent_pt->right;

            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else {
                if (pt == parent_pt->right) {
                    root = leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->par;
                }

                root = rightRotate(root, grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }

        else {
            struct node* uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    root = rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->par;
                }

                root = leftRotate(root, grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
    return root;
}
