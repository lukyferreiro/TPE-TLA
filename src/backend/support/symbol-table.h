#ifndef __SYMBOL_TABLE_H_
#define __SYMBOL_TABLE_H_

#include "abstract-syntax-tree.h"

typedef struct TreeVariable TreeVariable;

struct TreeVariable{
    char* name;
    TreeType treeType;
    IntegerArray* nodes;
    bool max;
    bool min;
    bool count;
    bool balanced;
    bool height;
};

TreeVariable* create_variable_st(char* treeName);

TreeVariable* get_variable_st(char* treeName);

#endif