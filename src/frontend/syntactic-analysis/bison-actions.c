#include "bison-actions.h"
#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/**
 * Implementación de "bison-grammar.h".
 */

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
 * Esta acción se corresponde con el no-terminal que representa el símbolo
 * inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
 * indica que efectivamente el programa de entrada se pudo generar con esta
 * gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
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
    //Constant* constant = malloc(sizeof(Constant));
    //.. TODO
    return 1;
}

ConstantArray* ConstantArrayGrammarAction(Constant* constant, ConstantArray* nextConstantArray) {
    LogDebug("\tConstantArrayGrammarAction");
    //... TODO
    return 2;
}

Constant* DeclarationGrammarAction(Declaration* declaration) {
    LogDebug("\tDeclarationGrammarAction(%d)", declaration);
    //Declaration* declaration = malloc(sizeof(Declaration));
    //... TODO
    return 3;
}

Constant* BlockGrammarAction(Block* block) {
    LogDebug("\tBlockGrammarAction(%d)", block);
    return 4;
}

Declaration* DeclarationTreeGrammarAction(TreeName* treeName, DeclarationParameters* declarationParameters) {
    LogDebug("\tDeclarationTreeGrammarAction(d, %d)", treeName, declarationParameters);
    return 5;
}

DeclarationParameters* DeclarationTreeParametersGrammarAction(IntegerParameters* treeIntegersParameters) {
    LogDebug("\tDeclarationTreeParametersGrammarAction(%d)", treeIntegersParameters);
    return 6;
}

IntegerParameters* IntegerParametersGrammarAction(IntegerArray* nodesIntegerArray) {
    LogDebug("\tIntegerParametersGrammarAction(%d)", nodesIntegerArray);
    return 7;
}

IntegerArray* IntegerConstantGrammarAction(Integer* node) {
    LogDebug("\tIntegerConstantGrammarAction(%d)", node);
    return 8;
}

IntegerArray* IntegerConstantArrayGrammarAction(Integer* node, IntegerArray* nextNodesIntegerArray) {
    LogDebug("\tIntegerConstantArrayGrammarAction(%d, %d)", node, nextNodesIntegerArray);
    return 9;
}

Block* ConfigureBlockGrammarAction(TreeType* treeType, TreeName* treeName, ConfigureBlock* configureBlock) {
    LogDebug("\tConfigureBlockGrammarAction(%d, %d, %d)", treeType, treeName, configureBlock);
    return 10;
}

Block* CreateBlockGrammarAction(FileName* fileName, CreateBlock* createBlock) {
    LogDebug("\tCreateBlockGrammarAction(%d, %d)", fileName, createBlock);
    return 11;
}

TreeType* TreeTypeBSTGrammarAction() {
    LogDebug("\tTreeTypeBSTGrammarAction");
    return 12;
}

TreeType* TreeTypeAVLGrammarAction() {
    LogDebug("\tTreeTypeAVLGrammarAction");
    return 13;
}

TreeType* TreeTypeRBTGrammarAction() {
    LogDebug("\tTreeTypeRBTGrammarAction");
    return 14;
}

ConfigureBlock* TreeSentencesGrammarAction(TreeSentences* treeSentences) {
    LogDebug("\tTreeSentencesGrammarAction(%d)", treeSentences);
    return 15;
}

TreeSentences* TreeSentenceGrammarAction(TreeSentence* treeSentence) {
    LogDebug("\tTreeSentenceGrammarAction(%d)", treeSentence);
    return 16;
}

TreeSentences* TreeSentenceArrayGrammarAction(TreeSentence* treeSentence, TreeSentences* nextTreeSentences) {
    LogDebug("\tTreeSentenceArrayGrammarAction(%d, %d)", treeSentence, nextTreeSentences);
    return 17;
}

TreeSentence* AddNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tAddNodeGrammarAction(%d)", integerParameters);
    return 18;
}

TreeSentence* DeleteNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tDeleteNodeGrammarAction(%d)", integerParameters);
    return 19;
}

TreeSentence* FindNodeGrammarAction(IntegerParameters* integerParameters) {
    LogDebug("\tFindNodeGrammarAction(%d)", integerParameters);
    return 20;
}
CreateBlock* FileSentencesGrammarAction(FileSentences* fileSentences) {
    LogDebug("\tFileSentencesGrammarAction(%d)", fileSentences);
    return 21;
}

FileSentences* FileSentenceGrammarAction(FileSentence* fileSentence) {
    LogDebug("\tFileSentenceGrammarAction(%d)", fileSentence);
    return 22;
}

FileSentences* FileSentenceArrayGrammarAction(FileSentence* fileSentence, FileSentences* nextFileSentences) {
    LogDebug("\tFileSentenceArrayGrammarAction(%d, %d)", fileSentence, nextFileSentences);
    return 23;
}

FileSentence* AddTreeGrammarAction(TreeParameters* treeParameters) {
    LogDebug("\tAddTreeGrammarAction(%d)", treeParameters);
    return 24;
}

FileSentence* AddFilePathGrammarAction(TreeParameters* fileParameter) {
    LogDebug("\tAddFilePathGrammarAction(%d)", fileParameter);
    return 25;
}

FileSentence* AddLegendGrammarAction(TreeParameters* legendParameters) {
    LogDebug("\tAddLegendGrammarAction(%d)", legendParameters);
    return 26;
}

TreeParameters* TreeParametersGrammarAction(TreeArray* treeArray) {
    LogDebug("\tTreeParametersGrammarAction(%d)", treeArray);
    return 27;
}

FileParameter* FileParameterSentenceGrammarAction(FilePath* filePath) {
    LogDebug("\tFileParameterSentenceGrammarAction(%d)", filePath);
    return 28;
}

TreeArray* TreeNameGrammarAction(TreeName* treeName) {
    LogDebug("\tTreeNameGrammarAction(%d)", treeName);
    return 29;
}
TreeArray* TreeNameArrayGrammarAction(TreeName* treeName, TreeArray* nextTreeNames) {
    LogDebug("\tTreeNameArrayGrammarAction(%d, %d)", treeName, nextTreeNames);
    return 30;
}

LegendParameters* LegendParametersGrammarAction(LegendArray* legendArray) {
    LogDebug("\tLegendParametersGrammarAction(%d)", legendArray);
    return 31;
}

LegendArray* LegendTypeGrammarAction(LegendType* legendType) {
    LogDebug("\tLegendTypeGrammarAction(%d)", legendType);
    return 32;
}

LegendArray* LegendTypeArrayGrammarAction(LegendType* legendType, LegendArray* nextLegendTypes) {
    LogDebug("\tLegendTypeArrayGrammarAction(%d, %d)", legendType, nextLegendTypes);
    return 33;
}

LegendType* LegendMaxGrammarAction() {
    LogDebug("\tLegendMaxGrammarAction");
    return 34;
}

LegendType* LegendMinGrammarAction() {
    LogDebug("\tLegendMinGrammarAction");
    return 35;
}

LegendType* LegendCountGrammarAction() {
    LogDebug("\tLegendCountGrammarAction");
    return 36;
}

LegendType* LegendBalancedGrammarAction() {
    LogDebug("\tLegendBalancedGrammarAction");
    return 37;
}

LegendType* LegendHeightGrammarAction() {
    LogDebug("\tLegendHeightGrammarAction");
    return 38;
}
