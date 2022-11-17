#include "symbol-table.h"
#include "../support/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

KHASH_MAP_INIT_STR(variables_hash_map, Variable*);
static khash_t(variables_hash_map) * variables_st;
static Variable* create_new_variable(char* name, VariableType type);

static Variable* create_new_var(char* name, VariableType type) {
    Variable* new = (Variable*)calloc(1, sizeof(new));
    new->treeType = type;
    new->name = name;
    return new;
}

void initialize_st(void) {
    variables_st = kh_init(variables_hash_map);
}

void free_st(void) {
    Variable* var;
    kh_foreach_value(variables_st, var, free(var));
    kh_destroy(variables_hash_map, variables_st);
}

Variable* create_variable_st(char* name, VariableType type) {
    if (!exists_variable_in_st(name)) {

        Variable* new = create_new_variable(name, type);

        int ret;
        khiter_t k = kh_put(variables_hash_map, variables_st, name, &ret);
        if (ret == -1) {
            return NULL;
        }

        kh_val(variables_st, k) = new;
        return new;
    }

    return NULL;
}

Variable* get_variable_st(char* name) {
    khiter_t k = kh_get(variables_hash_map, variables_st, name);
    if (k != kh_end(variables_st)) {
        return kh_val(variables_st, k);
    }

    return NULL;
}

boolean exists_variable_in_st(char* name) {
    khiter_t k = kh_get(variables_hash_map, variables_st, name);
    return k != kh_end(variables_st);
}