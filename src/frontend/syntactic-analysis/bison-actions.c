#include "bison-actions.h"
#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <string.h>

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
Program* ProgramGrammarAction(const ConstantArray* constantArray) {
    LogDebug("\tProgramGrammarAction(%d)", constantArray);
    /*
     * "state" es una variable global que almacena el estado del compilador,
     * cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
     * es utilizada en la función "main".
     */
    /* state.succeed = true; */
    /*
     * Por otro lado, "result" contiene el resultado de aplicar el análisis
     * sintáctico mediante Bison, y almacenar el nood raíz del AST construido
     * en esta variable. Para el ejemplo de la calculadora, no hay AST porque
     * la expresión se computa on-the-fly, y es la razón por la cual esta
     * variable es un simple entero, en lugar de un nodo.
     */
    /* state.result = value;
    return value; */
    return 1;
}

ConstantArray* ConstantGrammarAction(const Constant* constant) {
    LogDebug("\tConstantGrammarAction(%d)", constant);
    return 1;
}

ConstantArray* ConstantArrayGrammarAction(const Constant* constant, const ConstantArray* nextConstantArray) {
    LogDebug("\tConstantArrayGrammarAction(%d, %d)", constant, nextConstantArray);
    return 1;
}

Constant* DeclarationGrammarAction(const Declaration* declaration) {
    LogDebug("\tDeclarationGrammarAction(%d)", declaration);
    return 1;
}

Constant* BlockGrammarAction(const Block* block) {
    LogDebug("\tBlockGrammarAction(%d)", block);
    return 1;
}

Declaration* DeclarationTreeGrammarAction(const TreeName* treeName, const DeclarationParameters* declarationParameters) {
    LogDebug("\tDeclarationTreeGrammarAction(d, %d)", treeName, declarationParameters);
    return 1;
}

DeclarationParameters* DeclarationTreeParametersGrammarAction(const IntegerParameters* treeIntegersParameters) {
    LogDebug("\tDeclarationTreeParametersGrammarAction(%d)", treeIntegersParameters);
    return 1;
}

IntegerParameters* IntegerParametersGrammarAction(const IntegerArray* nodesIntegerArray) {
    LogDebug("\tIntegerParametersGrammarAction(%d)", nodesIntegerArray);
    return 1;
}

IntegerArray* IntegerConstantGrammarAction(const Integer* node) {
    LogDebug("\tIntegerConstantGrammarAction(%d)", node);
    return 1;
}

IntegerArray* IntegerConstantArrayGrammarAction(const Integer* node, const IntegerArray* nextNodesIntegerArray) {
    LogDebug("\tIntegerConstantArrayGrammarAction(%d, %d)", node, nextNodesIntegerArray);
    return 1;
}

Block* ConfigureBlockGrammarAction(const TreeType* treeType, const TreeName* treeName, const ConfigureBlock* configureBlock) {
    LogDebug("\tConfigureBlockGrammarAction(%d, %d, %d)", treeType, treeName, configureBlock);
    return 1;
}

Block* CreateBlockGrammarAction(const FileName* fileName, const CreateBlock* createBlock) {
    LogDebug("\tCreateBlockGrammarAction(%d, %d)", fileName, createBlock);
    return 1;
}

TreeType* TreeTypeBSTGrammarAction() {
    LogDebug("\tTreeTypeBSTGrammarAction");
    return 1;
}

TreeType* TreeTypeAVLGrammarAction() {
    LogDebug("\tTreeTypeAVLGrammarAction");
    return 1;
}

TreeType* TreeTypeRBTGrammarAction() {
    LogDebug("\tTreeTypeRBTGrammarAction");
    return 1;
}

ConfigureBlock* TreeSentencesGrammarAction(const TreeSentences* treeSentences) {
    LogDebug("\tTreeSentencesGrammarAction(%d)", treeSentences);
    return 1;
}

TreeSentences* TreeSentenceGrammarAction(const TreeSentence* treeSentence) {
    LogDebug("\tTreeSentenceGrammarAction(%d)", treeSentence);
    return 1;
}

TreeSentences* TreeSentenceArrayGrammarAction(const TreeSentence* treeSentence, const TreeSentences* nextTreeSentences) {
    LogDebug("\tTreeSentenceArrayGrammarAction(%d, %d)", treeSentence, nextTreeSentences);
    return 1;
}

TreeSentence* AddNodeGrammarAction(const IntegerParameters* integerParameters) {
    LogDebug("\tAddNodeGrammarAction(%d)", integerParameters);
    return 1;
}

TreeSentence* DeleteNodeGrammarAction(const IntegerParameters* integerParameters) {
    LogDebug("\tDeleteNodeGrammarAction(%d)", integerParameters);
    return 1;
}

TreeSentence* FindNodeGrammarAction(const IntegerParameters* integerParameters) {
    LogDebug("\tFindNodeGrammarAction(%d)", integerParameters);
    return 1;
}
CreateBlock* FileSentencesGrammarAction(const FileSentences* fileSentences) {
    LogDebug("\tFileSentencesGrammarAction(%d)", fileSentences);
    return 1;
}

FileSentences* FileSentenceGrammarAction(const FileSentence* fileSentence) {
    LogDebug("\tFileSentenceGrammarAction(%d)", fileSentence);
    return 1;
}

FileSentences* FileSentenceArrayGrammarAction(const FileSentence* fileSentence, const FileSentences* nextFileSentences) {
    LogDebug("\tFileSentenceArrayGrammarAction(%d, %d)", fileSentence, nextFileSentences);
    return 1;
}

FileSentence* AddTreeGrammarAction(const TreeParameters* treeParameters) {
    LogDebug("\tAddTreeGrammarAction(%d)", treeParameters);
    return 1;
}

FileSentence* AddFilePathGrammarAction(const TreeParameters* fileParameter) {
    LogDebug("\tAddFilePathGrammarAction(%d)", fileParameter);
    return 1;
}

FileSentence* AddLegendGrammarAction(const TreeParameters* legendParameters) {
    LogDebug("\tAddLegendGrammarAction(%d)", legendParameters);
    return 1;
}

TreeParameters* TreeParametersGrammarAction(const TreeArray* treeArray) {
    LogDebug("\tTreeParametersGrammarAction(%d)", treeArray);
    return 1;
}

FileParameter *FileParameterSentenceGrammarAction(const FilePath* filePath) {
    LogDebug("\tFileParameterSentenceGrammarAction(%d)", filePath);
    return 1;
}

TreeArray* TreeNameGrammarAction(const TreeName* treeName) {
    LogDebug("\tTreeNameGrammarAction(%d)", treeName);
    return 1;
}
TreeArray* TreeNameArrayGrammarAction(const TreeName* treeName, const TreeArray* nextTreeNames) {
    LogDebug("\tTreeNameArrayGrammarAction(%d, %d)", treeName, nextTreeNames);
    return 1;
}

LegendParameters* LegendParametersGrammarAction(const LegendArray* legendArray) {
    LogDebug("\tLegendParametersGrammarAction(%d)", legendArray);
    return 1;
}

LegendArray* LegendTypeGrammarAction(const LegendType* legendType) {
    LogDebug("\tLegendTypeGrammarAction(%d)", legendType);
    return 1;
}

LegendArray* LegendTypeArrayGrammarAction(const LegendType* legendType, const LegendArray* nextLegendTypes) {
    LogDebug("\tLegendTypeArrayGrammarAction(%d, %d)", legendType, nextLegendTypes);
    return 1;
}

LegendType* LegendMaxGrammarAction() {
    LogDebug("\tLegendMaxGrammarAction");
    return 1;
}

LegendType* LegendMinGrammarAction() {
    LogDebug("\tLegendMinGrammarAction");
    return 1;
}

LegendType* LegendCountGrammarAction() {
    LogDebug("\tLegendCountGrammarAction");
    return 1;
}

LegendType* LegendBalancedGrammarAction() {
    LogDebug("\tLegendBalancedGrammarAction");
    return 1;
}

LegendType* LegendHeightGrammarAction() {
    LogDebug("\tLegendHeightGrammarAction");
    return 1;
}
