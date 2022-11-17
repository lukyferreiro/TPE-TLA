#include "bison-actions.h"
#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

static Integer* createInteger(int integer);
static TreeName* createTreeName(char* treeName);
static FileName* createFileName(char* fileName);
static FilePath* createFilePath(char* filePath);

static Integer* createInteger(int integer) {
    LogDebug("\tInteger");
    Integer* i = (Integer*) calloc(1, sizeof(Integer));
    i->value = integer;
    return i;
}

static TreeName* createTreeName(char* treeName) {
    LogDebug("\tTreeName");
    TreeName* t = (TreeName*) calloc(1, sizeof(TreeName));
    t->name = treeName;
    return t;
}

static FileName* createFileName(char* fileName) {
    LogDebug("\tTreeName");
    FileName* t = (FileName*) calloc(1, sizeof(FileName));
    t->name = fileName;
    return t;
}

static FilePath* createFilePath(char* filePath) {
    LogDebug("\tTreeName");
    FilePath* t = (FilePath*) calloc(1, sizeof(FilePath));
    t->file_path = filePath;
    return t;
}

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
    Program* program = (Program*) calloc(1, sizeof(Program));
    program->constantArray = constantArray;
    state.succeed = TRUE;
    state.program = program;
    return program;
}

ConstantArray* ConstantGrammarAction(Constant* constant) {
    LogDebug("\tConstantGrammarAction");
    ConstantArray* c = (ConstantArray*) calloc(1, sizeof(ConstantArray));
    c->type = ONE_CONSTANT;
    c->constant = constant;
    c->nextConstantArray = NULL;
    return c;
}

ConstantArray* ConstantArrayGrammarAction(Constant* constant, ConstantArray* nextConstantArray) {
    LogDebug("\tConstantArrayGrammarAction");
    ConstantArray* c = (ConstantArray*) calloc(1, sizeof(ConstantArray));
    c->type = VARIOUS_CONSTANTS;
    c->constant = constant;
    c->nextConstantArray = nextConstantArray;
    return c;
}

Constant* DeclarationGrammarAction(Declaration* declaration) {
    LogDebug("\tDeclarationGrammarAction(%d)", declaration);
    Constant* c = (Constant*) calloc(1, sizeof(Constant));
    c->type = DECLARATION;
    c->declaration = declaration;
    c->block = NULL;
    return c;
}

Constant* BlockGrammarAction(Block* block) {
    LogDebug("\tBlockGrammarAction(%d)", block);
    Constant* c = (Constant*) calloc(1, sizeof(Constant));
    c->type = BLOCK;
    c->declaration = NULL;
    c->block = block;
    return c;
}

Declaration* DeclarationTreeGrammarAction(char* treeName, DeclarationParameters* declarationParameters) {
    LogDebug("\tDeclarationTreeGrammarAction(d, %d)", treeName, declarationParameters);
    Declaration* d = (Declaration*) calloc(1, sizeof(Declaration));
    d->treeName = createTreeName(treeName);
    d->declarationParameters = declarationParameters;
    return d;
}

DeclarationParameters* DeclarationTreeParametersGrammarAction(IntegerParameters* treeIntegersParameters) {
    LogDebug("\tDeclarationTreeParametersGrammarAction(%d)", treeIntegersParameters);
    DeclarationParameters* d = (DeclarationParameters*) calloc(1, sizeof(DeclarationParameters));
    d->integerParameters = treeIntegersParameters;
    return d;
}

IntegerParameters* IntegerParametersGrammarAction(IntegerArray* nodesIntegerArray) {
    LogDebug("\tIntegerParametersGrammarAction(%d)", nodesIntegerArray);
    IntegerParameters* i = (IntegerParameters*) calloc(1, sizeof(IntegerParameters));
    i->integerArray = nodesIntegerArray;
    return i;
}

IntegerArray* IntegerConstantGrammarAction(int node) {
    LogDebug("\tIntegerConstantGrammarAction(%d)", node);
    IntegerArray* i = (IntegerArray*) calloc(1, sizeof(IntegerArray));
    i->type = ONE_INTEGER;
    i->integer = createInteger(node);
    i->nextIntegerArray = NULL;
    return i;
}

IntegerArray* IntegerConstantArrayGrammarAction(int node, IntegerArray* nextNodesIntegerArray) {
    LogDebug("\tIntegerConstantArrayGrammarAction(%d, %d)", node, nextNodesIntegerArray);
    IntegerArray* i = (IntegerArray*) calloc(1, sizeof(IntegerArray));
    i->type = VARIOUS_INTEGER;
    i->integer = createInteger(node);
    i->nextIntegerArray = nextNodesIntegerArray;
    return i;
}

Block* ConfigureBlockGrammarAction(TreeType* treeType, char* treeName, ConfigureBlock* configureBlock) {
    LogDebug("\tConfigureBlockGrammarAction(%d, %d, %d)", treeType, treeName, configureBlock);
    Block* b = (Block*) calloc(1, sizeof(Block));
    b->type = CONFIGURE_BLOCK;
    b->treeType = treeType;
    b->treeName = createTreeName(treeName);
    b->fileName = NULL;
    b->configureBlock = configureBlock;
    b->createBlock = NULL;
    return b;
}

Block* CreateBlockGrammarAction(char* fileName, CreateBlock* createBlock) {
    LogDebug("\tCreateBlockGrammarAction(%d, %d)", fileName, createBlock);
    Block* b = (Block*) calloc(1, sizeof(Block));
    b->type = CREATE_BLOCK;
    b->treeType = NULL;
    b->treeName = NULL;
    b->fileName = createFileName(fileName);
    b->configureBlock = NULL;
    b->createBlock = createBlock;
    return b;
}

TreeType TreeTypeBSTGrammarAction() {
    LogDebug("\tTreeTypeBSTGrammarAction");
    return BST_TYPE;
}

TreeType TreeTypeAVLGrammarAction() {
    LogDebug("\tTreeTypeAVLGrammarAction");
    return AVL_TYPE;
}

TreeType TreeTypeRBTGrammarAction() {
    LogDebug("\tTreeTypeRBTGrammarAction");
    return RBT_TYPE;
}

ConfigureBlock* TreeSentencesGrammarAction(TreeSentences* treeSentences) {
    LogDebug("\tTreeSentencesGrammarAction(%d)", treeSentences);
    ConfigureBlock* c = (ConfigureBlock*) calloc(1, sizeof(ConfigureBlock));
    c->treeSentences = treeSentences;
    return c;
}

TreeSentences* TreeSentenceGrammarAction(TreeSentence* treeSentence) {
    LogDebug("\tTreeSentenceGrammarAction(%d)", treeSentence);
    TreeSentences* t = (TreeSentences*) calloc(1, sizeof(TreeSentences));
    t->type = ONE_TREE_SENTENCE;
    t->treeSentence = treeSentence;
    t->nextTreeSentences = NULL;
    return t;
}

TreeSentences* TreeSentenceArrayGrammarAction(TreeSentence* treeSentence, TreeSentences* nextTreeSentences) {
    LogDebug("\tTreeSentenceArrayGrammarAction(%d, %d)", treeSentence, nextTreeSentences);
    TreeSentences* t = (TreeSentences*) calloc(1, sizeof(TreeSentences));
    t->type = VARIOUS_TREE_SENTENCES;
    t->treeSentence = treeSentence;
    t->nextTreeSentences = nextTreeSentences;
    return t;
}

TreeSentence* AddNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tAddNodeGrammarAction(%d)", integerParameters);
    TreeSentence* t = (TreeSentence*) calloc(1, sizeof(TreeSentence));
    t->type = ADD_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

TreeSentence* DeleteNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tDeleteNodeGrammarAction(%d)", integerParameters);
    TreeSentence* t = (TreeSentence*) calloc(1, sizeof(TreeSentence));
    t->type = DELETE_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

TreeSentence* FindNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tFindNodeGrammarAction(%d)", integerParameters);
    TreeSentence* t = (TreeSentence*) calloc(1, sizeof(TreeSentence));
    t->type = FIND_NODE_SENTENCE;
    t->integerParameters = integerParameters;
    return t;
}

CreateBlock* FileSentencesGrammarAction(FileSentences* fileSentences) {
    LogDebug("\tFileSentencesGrammarAction(%d)", fileSentences);
    CreateBlock* c = (CreateBlock*) calloc(1, sizeof(CreateBlock));
    c->fileSentences = fileSentences;
    return c;
}

FileSentences* FileSentenceGrammarAction(FileSentence* fileSentence) {
    LogDebug("\tFileSentenceGrammarAction(%d)", fileSentence);
    FileSentences* f = (FileSentences*) calloc(1, sizeof(FileSentences));
    f->type = ONE_FILE_SENTENCE;
    f->fileSentence = fileSentence;
    f->nextFileSentences = NULL;
    return f;
}

FileSentences* FileSentenceArrayGrammarAction(FileSentence* fileSentence, FileSentences* nextFileSentences) {
    LogDebug("\tFileSentenceArrayGrammarAction(%d, %d)", fileSentence, nextFileSentences);
    FileSentences* f = (FileSentences*) calloc(1, sizeof(FileSentences));
    f->type = VARIOUS_FILE_SENTENCES;
    f->fileSentence = fileSentence;
    f->nextFileSentences = nextFileSentences;
    return f;
}

FileSentence* AddTreeGrammarAction(TreeParameters* treeParameters) {
    LogDebug("\tAddTreeGrammarAction(%d)", treeParameters);
    FileSentence* f = (FileSentence*) calloc(1, sizeof(FileSentence));
    f->type = ADD_TREE_SENTENCE;
    f->treeParameters = treeParameters;
    f->fileParameter = NULL;
    f->legendParameters = NULL;
    return f;
}

FileSentence* AddFilePathGrammarAction(TreeParameters* fileParameter) {
    LogDebug("\tAddFilePathGrammarAction(%d)", fileParameter);
    FileSentence* f = (FileSentence*) calloc(1, sizeof(FileSentence));
    f->type = ADD_FILE_PATH_SENTENCE;
    f->treeParameters = NULL;
    f->fileParameter = fileParameter;
    f->legendParameters = NULL;
    return f;
}

FileSentence* AddLegendGrammarAction(TreeParameters* legendParameters) {
    LogDebug("\tAddLegendGrammarAction(%d)", legendParameters);
    FileSentence* f = (FileSentence*) calloc(1, sizeof(FileSentence));
    f->type = ADD_LEGEND_SENTENCE;
    f->treeParameters = NULL;
    f->fileParameter = NULL;
    f->legendParameters = legendParameters;
    return f;
}

TreeParameters* TreeParametersGrammarAction(TreeArray* treeArray) {
    LogDebug("\tTreeParametersGrammarAction(%d)", treeArray);
    TreeParameters* t = (TreeParameters*) calloc(1, sizeof(TreeParameters));
    t->treeArray = treeArray;
    return t;
}

FileParameter* FileParameterSentenceGrammarAction(char* filePath) {
    LogDebug("\tFileParameterSentenceGrammarAction(%d)", filePath);
    FileParameter* f = (FileParameter*) calloc(1, sizeof(FileParameter));
    f->filePath = createFilePath(filePath);
    return f;
}

TreeArray* TreeNameGrammarAction(char* treeName) {
    LogDebug("\tTreeNameGrammarAction(%d)", treeName);
    TreeArray* t = (TreeArray*) calloc(1, sizeof(TreeArray));
    t->type = ONE_TREE;
    t->treeName = createTreeName(treeName);
    t->nextTreeArray = NULL;
    return t;
}

TreeArray* TreeNameArrayGrammarAction(char* treeName, TreeArray* nextTreeNames) {
    LogDebug("\tTreeNameArrayGrammarAction(%d, %d)", treeName, nextTreeNames);
    TreeArray* t = (TreeArray*) calloc(1, sizeof(TreeArray));
    t->type = VARIOUS_TREES;
    t->treeName = createTreeName(treeName);
    t->nextTreeArray = nextTreeNames;
    return t;
}

LegendParameters* LegendParametersGrammarAction(LegendArray* legendArray) {
    LogDebug("\tLegendParametersGrammarAction(%d)", legendArray);
    LegendParameters* l = (LegendParameters*) calloc(1, sizeof(LegendParameters));
    l->legendArray = legendArray;
    return l;
}

LegendArray* LegendTypeGrammarAction(LegendType* legendType) {
    LogDebug("\tLegendTypeGrammarAction(%d)", legendType);
    LegendArray* l = (LegendArray*) calloc(1, sizeof(LegendArray));
    l->type = ONE_LEGEND;
    l->legendType = legendType;
    l->nextLegendArray = NULL;
    return l;
}

LegendArray* LegendTypeArrayGrammarAction(LegendType* legendType, LegendArray* nextLegendTypes) {
    LogDebug("\tLegendTypeArrayGrammarAction(%d, %d)", legendType, nextLegendTypes);
    LegendArray* l = (LegendArray*) calloc(1, sizeof(LegendArray));
    l->type = VARIOUS_LEGENDS;
    l->legendType = legendType;
    l->nextLegendArray = nextLegendTypes;
    return l;
}

LegendType LegendMaxGrammarAction() {
    LogDebug("\tLegendMaxGrammarAction");
    return MAX_LEGEND;
}

LegendType LegendMinGrammarAction() {
    LogDebug("\tLegendMinGrammarAction");
    return MIN_LEGEND;
}

LegendType LegendCountGrammarAction() {
    LogDebug("\tLegendCountGrammarAction");
    return COUNT_LEGEND;
}

LegendType LegendBalancedGrammarAction() {
    LogDebug("\tLegendBalancedGrammarAction");
    return BALANCED_LEGEND;
}

LegendType LegendHeightGrammarAction() {
    LogDebug("\tLegendHeightGrammarAction");
    return HEIGHT_LEGEND;
}
