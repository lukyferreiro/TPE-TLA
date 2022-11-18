#include "bison-actions.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Esta función se ejecuta cada vez que se emite un error de sintaxis.
 */
void yyerror(const char* string) {
    LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
    LogError("En ASCII es:");
    LogErrorRaw("\t");
    const int length = strlen(yytext);
    for (int i = 0; i < length; ++i) {
        LogErrorRaw("[%d]", yytext[i]);
    }
    LogErrorRaw("\n\n");
}

/**
 * Esta acción se corresponde con el no-terminal que representa el símbolo inicial de la gramática,
 * y por ende, es el último en ser ejecutado, lo que indica que efectivamente el programa de entrada
 * se pudo generar con esta gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
 */
Program* ProgramGrammarAction(ConstantArray* constantArray) {
    LogDebug("\tProgramGrammarAction");
    Program* program = (Program*)calloc(1, sizeof(Program));
    program->constantArray = constantArray;
    state.succeed = TRUE;
    state.program = program;
    return program;
}

ConstantArray* ConstantGrammarAction(Constant* constant) {
    LogDebug("\tConstantGrammarAction");
    ConstantArray* c = (ConstantArray*)calloc(1, sizeof(ConstantArray));
    c->type = ONE_CONSTANT;
    c->constant = constant;
    c->nextConstantArray = NULL;
    return c;
}

ConstantArray* ConstantArrayGrammarAction(Constant* constant, ConstantArray* nextConstantArray) {
    LogDebug("\tConstantArrayGrammarAction");
    ConstantArray* c = (ConstantArray*)calloc(1, sizeof(ConstantArray));
    c->type = VARIOUS_CONSTANTS;
    c->constant = constant;
    c->nextConstantArray = nextConstantArray;
    return c;
}

Constant* DeclarationGrammarAction(Declaration* declaration) {
    LogDebug("\tDeclarationGrammarAction");
    Constant* c = (Constant*)calloc(1, sizeof(Constant));
    c->type = DECLARATION;
    c->declaration = declaration;
    c->block = NULL;
    return c;
}

Constant* BlockGrammarAction(Block* block) {
    LogDebug("\tBlockGrammarAction");
    Constant* c = (Constant*)calloc(1, sizeof(Constant));
    c->type = BLOCK;
    c->declaration = NULL;
    c->block = block;
    return c;
}

Declaration* DeclarationTreeGrammarAction(char* treeName, DeclarationParameters* declarationParameters) {
    LogDebug("\tDeclarationTreeGrammarAction(%s)", treeName);

    //Me fijo si ya esta declarada en la tabla de simbolos
    if (create_variable_st(treeName, VARIABLE_TREE) == NULL) {
        LogError("El arbol %s ya estaba declarado\n", treeName);
        exit(1);    //TODO sacar el exit y levantar flag de syntax error
    }

    Declaration* d = (Declaration*)calloc(1, sizeof(Declaration));
    d->treeName = treeName;
    d->declarationParameters = declarationParameters;
    return d;
}

DeclarationParameters* DeclarationTreeParametersGrammarAction(IntegerParameters* treeIntegersParameters) {
    LogDebug("\tDeclarationTreeParametersGrammarAction");
    DeclarationParameters* d = (DeclarationParameters*)calloc(1, sizeof(DeclarationParameters));
    d->integerParameters = treeIntegersParameters;
    return d;
}

IntegerParameters* IntegerParametersGrammarAction(IntegerArray* nodesIntegerArray) {
    LogDebug("\tIntegerParametersGrammarAction");
    IntegerParameters* i = (IntegerParameters*)calloc(1, sizeof(IntegerParameters));
    i->integerArray = nodesIntegerArray;
    return i;
}

IntegerArray* IntegerConstantGrammarAction(int node) {
    LogDebug("\tIntegerConstantGrammarAction(%d)", node);
    IntegerArray* i = (IntegerArray*)calloc(1, sizeof(IntegerArray));
    i->type = ONE_INTEGER;
    i->value = node;
    i->nextIntegerArray = NULL;
    return i;
}

IntegerArray* IntegerConstantArrayGrammarAction(int node, IntegerArray* nextNodesIntegerArray) {
    LogDebug("\tIntegerConstantArrayGrammarAction(%d)", node);
    IntegerArray* i = (IntegerArray*)calloc(1, sizeof(IntegerArray));
    i->type = VARIOUS_INTEGER;
    i->value = node;
    i->nextIntegerArray = nextNodesIntegerArray;
    return i;
}

Block* ConfigureBlockGrammarAction(TreeTypeStruct* treeType, char* treeName, ConfigureBlock* configureBlock) {
    LogDebug("\tConfigureBlockGrammarAction(%s)", treeName);

    Variable* var = get_variable_st(treeName);
    if (var == NULL) {
        LogError("El arbol %s no esta declarado", treeName);
        exit(1);
    }

    if (var->type == VARIABLE_TREE) {
        Block* b = (Block*)calloc(1, sizeof(Block));
        b->type = CONFIGURE_BLOCK;
        b->treeType = treeType;
        b->treeName = treeName;
        b->fileName = NULL;
        b->configureBlock = configureBlock;
        b->createBlock = NULL;
        return b;
    } else {
        // Si estoy aca, ya existe esta variable, pero es del tipo FILE_PATH
        LogError("La variable 'tree' %s ya se encuentra declarada como un file path", treeName);
        exit(1);
    }
}

Block* CreateBlockGrammarAction(char* fileName, CreateBlock* createBlock) {
    LogDebug("\tCreateBlockGrammarAction(%s)", fileName);
    
    //Me fijo si ya esta declarada en la tabla de simbolos
    if (create_variable_st(fileName, VARIABLE_FILE) == NULL) {
        LogError("Ya se encuentra declarado un archivo con el nombre %s\n", fileName);
        exit(1);    //TODO sacar el exit y levantar flag de syntax error
    }

    Block* b = (Block*)calloc(1, sizeof(Block));
    b->type = CREATE_BLOCK;
    b->treeType = NULL;
    b->treeName = NULL;
    b->fileName = fileName;
    b->configureBlock = NULL;
    b->createBlock = createBlock;
    return b;
}

TreeTypeStruct* TreeTypeBSTGrammarAction() {
    LogDebug("\tTreeTypeBSTGrammarAction");
    TreeTypeStruct* t = (TreeTypeStruct*)calloc(1, sizeof(TreeTypeStruct));
    t->treeType = BST_TYPE;
    return t;
}

TreeTypeStruct* TreeTypeAVLGrammarAction() {
    LogDebug("\tTreeTypeAVLGrammarAction");
    TreeTypeStruct* t = (TreeTypeStruct*)calloc(1, sizeof(TreeTypeStruct));
    t->treeType = AVL_TYPE;
    return t;
}

TreeTypeStruct* TreeTypeRBTGrammarAction() {
    LogDebug("\tTreeTypeRBTGrammarAction");
    TreeTypeStruct* t = (TreeTypeStruct*)calloc(1, sizeof(TreeTypeStruct));
    t->treeType = RBT_TYPE;
    return t;
}

ConfigureBlock* TreeSentencesGrammarAction(TreeSentences* treeSentences) {
    LogDebug("\tTreeSentencesGrammarAction");
    ConfigureBlock* c = (ConfigureBlock*)calloc(1, sizeof(ConfigureBlock));
    c->treeSentences = treeSentences;
    return c;
}

TreeSentences* TreeSentenceGrammarAction(TreeSentence* treeSentence) {
    LogDebug("\tTreeSentenceGrammarAction");
    TreeSentences* t = (TreeSentences*)calloc(1, sizeof(TreeSentences));
    t->type = ONE_TREE_SENTENCE;
    t->treeSentence = treeSentence;
    t->nextTreeSentences = NULL;
    return t;
}

TreeSentences* TreeSentenceArrayGrammarAction(TreeSentence* treeSentence, TreeSentences* nextTreeSentences) {
    LogDebug("\tTreeSentenceArrayGrammarAction");
    TreeSentences* t = (TreeSentences*)calloc(1, sizeof(TreeSentences));
    t->type = VARIOUS_TREE_SENTENCES;
    t->treeSentence = treeSentence;
    t->nextTreeSentences = nextTreeSentences;
    return t;
}

TreeSentence* AddNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tAddNodeGrammarAction");
    TreeSentence* t = (TreeSentence*)calloc(1, sizeof(TreeSentence));
    t->type = ADD_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

TreeSentence* DeleteNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tDeleteNodeGrammarAction");
    TreeSentence* t = (TreeSentence*)calloc(1, sizeof(TreeSentence));
    t->type = DELETE_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

TreeSentence* FindNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tFindNodeGrammarAction");
    TreeSentence* t = (TreeSentence*)calloc(1, sizeof(TreeSentence));
    t->type = FIND_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

CreateBlock* FileSentencesGrammarAction(FileSentences* fileSentences) {
    LogDebug("\tFileSentencesGrammarAction");
    CreateBlock* c = (CreateBlock*)calloc(1, sizeof(CreateBlock));
    c->fileSentences = fileSentences;
    return c;
}

FileSentences* FileSentenceGrammarAction(FileSentence* fileSentence) {
    LogDebug("\tFileSentenceGrammarAction");
    FileSentences* f = (FileSentences*)calloc(1, sizeof(FileSentences));
    f->type = ONE_FILE_SENTENCE;
    f->fileSentence = fileSentence;
    f->nextFileSentences = NULL;
    return f;
}

FileSentences* FileSentenceArrayGrammarAction(FileSentence* fileSentence, FileSentences* nextFileSentences) {
    LogDebug("\tFileSentenceArrayGrammarAction");
    FileSentences* f = (FileSentences*)calloc(1, sizeof(FileSentences));
    f->type = VARIOUS_FILE_SENTENCES;
    f->fileSentence = fileSentence;
    f->nextFileSentences = nextFileSentences;
    return f;
}

FileSentence* AddTreeGrammarAction(TreeParameters* treeParameters) {
    LogDebug("\tAddTreeGrammarAction");
    FileSentence* f = (FileSentence*)calloc(1, sizeof(FileSentence));
    f->type = ADD_TREE_SENTENCE;
    f->treeParameters = treeParameters;
    f->fileParameter = NULL;
    f->legendParameters = NULL;
    return f;
}

FileSentence* AddFilePathGrammarAction(FileParameter* fileParameter) {
    LogDebug("\tAddFilePathGrammarAction");
    FileSentence* f = (FileSentence*)calloc(1, sizeof(FileSentence));
    f->type = ADD_FILE_PATH_SENTENCE;
    f->treeParameters = NULL;
    f->fileParameter = fileParameter;
    f->legendParameters = NULL;
    return f;
}

FileSentence* AddLegendGrammarAction(LegendParameters* legendParameters) {
    LogDebug("\tAddLegendGrammarAction");
    FileSentence* f = (FileSentence*)calloc(1, sizeof(FileSentence));
    f->type = ADD_LEGEND_SENTENCE;
    f->treeParameters = NULL;
    f->fileParameter = NULL;
    f->legendParameters = legendParameters;
    return f;
}

TreeParameters* TreeParametersGrammarAction(TreeArray* treeArray) {
    LogDebug("\tTreeParametersGrammarAction");
    TreeParameters* t = (TreeParameters*)calloc(1, sizeof(TreeParameters));
    t->treeArray = treeArray;
    return t;
}

FileParameter* FileParameterSentenceGrammarAction(char* filePath) {
    LogDebug("\tFileParameterSentenceGrammarAction(%s)", filePath);
    FileParameter* f = (FileParameter*)calloc(1, sizeof(FileParameter));
    f->filePath = filePath;
    return f;
}

TreeArray* TreeNameGrammarAction(char* treeName) {
    LogDebug("\tTreeNameGrammarAction(%s)", treeName);

    Variable* var = get_variable_st(treeName);
    if (var == NULL) {
        LogError("El arbol %s no esta declarado", treeName);
        exit(1);
    }

    if (var->type == VARIABLE_TREE) {
        TreeArray* t = (TreeArray*)calloc(1, sizeof(TreeArray));
        t->type = ONE_TREE;
        t->treeName = treeName;
        t->nextTreeArray = NULL;
        return t;
    } else {
        // Si estoy aca, ya existe esta variable, pero es del tipo FILE_PATH
        LogError("La variable 'tree' %s ya se encuentra declarada como un file path", treeName);
        exit(1);
    }
}

TreeArray* TreeNameArrayGrammarAction(char* treeName, TreeArray* nextTreeNames) {
    LogDebug("\tTreeNameArrayGrammarAction(%s)", treeName);

    Variable* var = get_variable_st(treeName);
    if (var == NULL) {
        LogError("El arbol %s no esta declarado", treeName);
        exit(1);
    }

    if (var->type == VARIABLE_TREE) {
        TreeArray* t = (TreeArray*)calloc(1, sizeof(TreeArray));
        t->type = VARIOUS_TREES;
        t->treeName = treeName;
        t->nextTreeArray = nextTreeNames;
        return t;
    } else {
        // Si estoy aca, ya existe esta variable, pero es del tipo FILE_PATH
        LogError("La variable 'tree' %s ya se encuentra declarada como un file path", treeName);
        exit(1);
    }
}

LegendParameters* LegendParametersGrammarAction(LegendArray* legendArray) {
    LogDebug("\tLegendParametersGrammarAction");
    LegendParameters* l = (LegendParameters*)calloc(1, sizeof(LegendParameters));
    l->legendArray = legendArray;
    return l;
}

LegendArray* LegendTypeGrammarAction(LegendTypeStruct* legendType) {
    LogDebug("\tLegendTypeGrammarAction");
    LegendArray* l = (LegendArray*)calloc(1, sizeof(LegendArray));
    l->type = ONE_LEGEND;
    l->legendType = legendType;
    l->nextLegendArray = NULL;
    return l;
}

LegendArray* LegendTypeArrayGrammarAction(LegendTypeStruct* legendType, LegendArray* nextLegendTypes) {
    LogDebug("\tLegendTypeArrayGrammarAction");
    LegendArray* l = (LegendArray*)calloc(1, sizeof(LegendArray));
    l->type = VARIOUS_LEGENDS;
    l->legendType = legendType;
    l->nextLegendArray = nextLegendTypes;
    return l;
}

LegendTypeStruct* LegendMaxGrammarAction() {
    LogDebug("\tLegendMaxGrammarAction");
    LegendTypeStruct* l = (LegendTypeStruct*)calloc(1, sizeof(LegendTypeStruct));
    l->legendType = MAX_LEGEND;
    return l;
}

LegendTypeStruct* LegendMinGrammarAction() {
    LogDebug("\tLegendMinGrammarAction");
    LegendTypeStruct* l = (LegendTypeStruct*)calloc(1, sizeof(LegendTypeStruct));
    l->legendType = MIN_LEGEND;
    return l;
}

LegendTypeStruct* LegendCountGrammarAction() {
    LogDebug("\tLegendCountGrammarAction");
    LegendTypeStruct* l = (LegendTypeStruct*)calloc(1, sizeof(LegendTypeStruct));
    l->legendType = COUNT_LEGEND;
    return l;
}

LegendTypeStruct* LegendBalancedGrammarAction() {
    LogDebug("\tLegendBalancedGrammarAction");
    LegendTypeStruct* l = (LegendTypeStruct*)calloc(1, sizeof(LegendTypeStruct));
    l->legendType = BALANCED_LEGEND;
    return l;
}

LegendTypeStruct* LegendHeightGrammarAction() {
    LogDebug("\tLegendHeightGrammarAction");
    LegendTypeStruct* l = (LegendTypeStruct*)calloc(1, sizeof(LegendTypeStruct));
    l->legendType = HEIGHT_LEGEND;
    return l;
}
