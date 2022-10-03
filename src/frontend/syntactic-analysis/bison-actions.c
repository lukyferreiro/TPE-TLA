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
int ProgramGrammarAction(const int value) {
    LogDebug("\tProgramGrammarAction(%d)", value);
    /*
     * "state" es una variable global que almacena el estado del compilador,
     * cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
     * es utilizada en la función "main".
     */
    state.succeed = true;
    /*
     * Por otro lado, "result" contiene el resultado de aplicar el análisis
     * sintáctico mediante Bison, y almacenar el nood raíz del AST construido
     * en esta variable. Para el ejemplo de la calculadora, no hay AST porque
     * la expresión se computa on-the-fly, y es la razón por la cual esta
     * variable es un simple entero, en lugar de un nodo.
     */
    state.result = value;
    return value;
}

int ConstantGrammarAction(const int constant) {
    LogDebug("\tConstantGrammarAction(%d)", constant);
    return 1;
}

int ConstantArrayGrammarAction(const int constant, const int nextConstantArray) {
    LogDebug("\tConstantArrayGrammarAction(%d, %d)", constant, nextConstantArray);
    return 1;
}

int DeclarationGrammarAction(const int declaration) {
    LogDebug("\tDeclarationGrammarAction(%d)", declaration);
    return 1;
}

int BlockGrammarAction(const int block) {
    LogDebug("\tBlockGrammarAction(%d)", block);
    return 1;
}

int DeclarationTreeGrammarAction(const char* treeName, const int declarationParameters) {
    LogDebug("\tDeclarationTreeGrammarAction(%s, %d)", treeName, declarationParameters);
    return 1;
}

int DeclarationTreeParametersGrammarAction(const int treeParameters) {
    LogDebug("\tDeclarationTreeParametersGrammarAction(%d)", treeParameters);
    return 1;
}

int IntegerParametersGrammarAction(const int nodesArray) {
    LogDebug("\tIntegerParametersGrammarAction(%d)", nodesArray);
    return 1;
}

int IntegerConstantGrammarAction(const int node) {
    LogDebug("\tIntegerConstantGrammarAction(%d)", node);
    return 1;
}

int IntegerConstantArrayGrammarAction(const int node, const int nextNode) {
    LogDebug("\tIntegerConstantArrayGrammarAction(%d, %d)", node, nextNode);
    return 1;
}

int ConfigureBlockGrammarAction(const int treeType, const char* treeName, const int configureBlock) {
    LogDebug("\tConfigureBlockGrammarAction(%d, %s, %d)", treeType, treeName, configureBlock);
    return 1;
}

int CreateBlockGrammarAction(const char* fileName, const int createBlock) {
    LogDebug("\tCreateBlockGrammarAction(%s, %d)", fileName, createBlock);
    return 1;
}

int TreeTypeBSTGrammarAction() {
    LogDebug("\tTreeTypeBSTGrammarAction");
    return 1;
}

int TreeTypeAVLGrammarAction() {
    LogDebug("\tTreeTypeAVLGrammarAction");
    return 1;
}

int TreeTypeRBTGrammarAction() {
    LogDebug("\tTreeTypeRBTGrammarAction");
    return 1;
}

int TreeSentencesGrammarAction(const int treeSentences) {
    LogDebug("\tTreeSentencesGrammarAction(%d)", treeSentences);
    return 1;
}

int TreeSentenceGrammarAction(const int treeSentence) {
    LogDebug("\tTreeSentenceGrammarAction(%d)", treeSentence);
    return 1;
}

int TreeSentenceArrayGrammarAction(const int treeSentence, const int nextTreeSentence) {
    LogDebug("\tTreeSentenceArrayGrammarAction(%d, %d)", treeSentence, nextTreeSentence);
    return 1;
}

int AddNodeGrammarAction(const int integerParameters) {
    LogDebug("\tAddNodeGrammarAction(%d)", integerParameters);
    return 1;
}

int DeleteNodeGrammarAction(const int integerParameters) {
    LogDebug("\tDeleteNodeGrammarAction(%d)", integerParameters);
    return 1;
}

int FindNodeGrammarAction(const int integerParameters) {
    LogDebug("\tFindNodeGrammarAction(%d)", integerParameters);
    return 1;
}

int FileSentencesGrammarAction(const int fileSentences) {
    LogDebug("\tFileSentencesGrammarAction(%d)", fileSentences);
    return 1;
}

int FileSentenceGrammarAction(const int fileSentence) {
    LogDebug("\tFileSentenceGrammarAction(%d)", fileSentence);
    return 1;
}

int FileSentenceArrayGrammarAction(const int fileSentence, const int nextFileSentence) {
    LogDebug("\tFileSentenceArrayGrammarAction(%d, %d)", fileSentence, nextFileSentence);
    return 1;
}

int AddTreeGrammarAction(const int treeParameters) {
    LogDebug("\tAddTreeGrammarAction(%d)", treeParameters);
    return 1;
}

int AddSavePathGrammarAction(const int fileParameter) {
    LogDebug("\tAddSavePathGrammarAction(%d)", fileParameter);
    return 1;
}

int AddLegendGrammarAction(const int legendParameters) {
    LogDebug("\tAddLegendGrammarAction(%d)", legendParameters);
    return 1;
}

int TreeParametersGrammarAction(const int treeArray) {
    LogDebug("\tTreeParametersGrammarAction(%d)", treeArray);
    return 1;
}

int FileParameterSentenceGrammarAction(const char* fileName) {
    LogDebug("\tFileParameterSentenceGrammarAction(%s)", fileName);
    return 1;
}

int TreeNameGrammarAction(const char* treeName) {
    LogDebug("\tTreeNameGrammarAction(%s)", treeName);
    return 1;
}

int TreeNameArrayGrammarAction(const char* treeName, const int nextTreeName) {
    LogDebug("\tTreeNameArrayGrammarAction(%s, %d)", treeName, nextTreeName);
    return 1;
}

int LegendParametersGrammarAction(const int legendArray) {
    LogDebug("\tLegendParametersGrammarAction(%d)", legendArray);
    return 1;
}

int LegendTypeGrammarAction(const int legendType) {
    LogDebug("\tLegendTypeGrammarAction(%d)", legendType);
    return 1;
}

int LegendTypeArrayGrammarAction(const int legendType, const int nextLegendType) {
    LogDebug("\tLegendTypeArrayGrammarAction(%d, %d)", legendType, nextLegendType);
    return 1;
}

int LegendMaxGrammarAction() {
    LogDebug("\tLegendMaxGrammarAction");
    return 1;
}

int LegendMinGrammarAction() {
    LogDebug("\tLegendMinGrammarAction");
    return 1;
}

int LegendCountGrammarAction() {
    LogDebug("\tLegendCountGrammarAction");
    return 1;
}

int LegendBalancedGrammarAction() {
    LogDebug("\tLegendBalancedGrammarAction");
    return 1;
}

int LegendHeightGrammarAction() {
    LogDebug("\tLegendHeightGrammarAction");
    return 1;
}
