#ifndef __SYMBOL_TABLE_H_
#define __SYMBOL_TABLE_H_

#include "abstract-syntax-tree.h"
#include "../support/khash.h"
#include "../support/shared.h"

typedef enum {
    VARIABLE_TREE,
    VARIABLE_FILE
} VariableType;

typedef struct Variable Variable;

struct Variable {
    VariableType type;
    char* name;
};

void initialize_st(void);
void free_st(void);
Variable* create_variable_st(char* treeName, VariableType type);
Variable* get_variable_st(char* treeName);
boolean exists_variable_in_st(char* treeName);

#endif