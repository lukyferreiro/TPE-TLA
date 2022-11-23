#include <stdio.h>
#include <stdlib.h>
#include "rbt_tree.h"


static struct node* newRbtNode(int key);
static struct node* bstInsertNode(struct node* trav, struct node* temp, int* flag);
static struct node* rightrotate(struct node* root, struct node* x);
static struct node* lefttrotate(struct node* root, struct node* x);
static struct node* fixup(struct node* root, struct node* pt);


struct node* insertRbtNode(struct node* node, int key, int* flag) {
    struct node* toAdd = newRbtNode(key);
    node = bstInsertNode(node, toAdd, flag);
    node = fixup(node, toAdd);
    return node;
}

static struct node* newRbtNode(int key) {
    struct node* temp = (struct node*)calloc(1, sizeof(struct node));
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
    }

    (*flag)=1;
    return trav;
}

static struct node* rightrotate(struct node* root, struct node* x) {
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

struct node* leftrotate(struct node* root, struct node* x) {
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

// This function fixes violations
// caused by BST insertion
static struct node* fixup(struct node* root, struct node* pt) {
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) && (pt->par->color == RED)) {
        parent_pt = pt->par;
        grand_parent_pt = pt->par->par;

        /* Case : A
            Parent of pt is left child
            of Grand-parent of
        pt */
        if (parent_pt == grand_parent_pt->left) {

            struct node* uncle_pt = grand_parent_pt->right;

            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else {

                /* Case : 2
                    pt is right child of its parent
                    Left-rotation required */
                if (pt == parent_pt->right) {
                    root = leftrotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->par;
                }

                /* Case : 3
                    pt is left child of its parent
                    Right-rotation required */
                root = rightrotate(root, grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }

        /* Case : B
            Parent of pt is right
            child of Grand-parent of
        pt */
        else {
            struct node* uncle_pt = grand_parent_pt->left;

            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                pt is left child of its parent
                Right-rotation required */
                if (pt == parent_pt->left) {
                    root = rightrotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->par;
                }

                /* Case : 3
                    pt is right child of its parent
                    Left-rotation required */
                root = leftrotate(root, grand_parent_pt);
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
