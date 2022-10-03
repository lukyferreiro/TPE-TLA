#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/support/shared.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

int ProgramGrammarAction(const int value);

int ConstantGrammarAction(const int constant);
int ConstantArrayGrammarAction(const int constant, const int nextConstantArray);

int DeclarationGrammarAction(const int declaration);
int BlockGrammarAction(const int block);

int DeclarationTreeGrammarAction(const char* treeName, const int declarationParameters);
int DeclarationTreeParametersGrammarAction(const int treeParameters);

int IntegerParametersGrammarAction(const int nodesArray);

int IntegerConstantGrammarAction(const int node);
int IntegerConstantArrayGrammarAction(const int node, const int nextNode);

int ConfigureBlockGrammarAction(const int treeType, const char* treeName, const int configureBlock);
int CreateBlockGrammarAction(const char* fileName, const int createBlock);

int TreeTypeBSTGrammarAction();
int TreeTypeAVLGrammarAction();
int TreeTypeRBTGrammarAction();

int TreeSentencesGrammarAction(const int treeSentences);

int TreeSentenceGrammarAction(const int treeSentence);
int TreeSentenceArrayGrammarAction(const int treeSentence, const int nextTreeSentence);

int AddNodeGrammarAction(const int integerParameters);
int DeleteNodeGrammarAction(const int integerParameters);
int FindNodeGrammarAction(const int integerParameters);

int FileSentencesGrammarAction(const int fileSentences);

int FileSentenceGrammarAction(const int fileSentence);
int FileSentenceArrayGrammarAction(const int fileSentence, const int nextFileSentence);

int AddTreeGrammarAction(const int treeParameters);
int AddSavePathGrammarAction(const int fileParameter);
int AddLegendGrammarAction(const int legendParameters);

int TreeParametersGrammarAction(const int treeArray);

int FileParameterSentenceGrammarAction(const char* fileName);

int TreeNameGrammarAction(const char* treeName);
int TreeNameArrayGrammarAction(const char* treeName, const int nextTreeName);

int LegendParametersGrammarAction(const int legendArray);

int LegendTypeGrammarAction(const int legendType);
int LegendTypeArrayGrammarAction(const int legendType, const int nexLegendType);

int LegendMaxGrammarAction();
int LegendMinGrammarAction();
int LegendCountGrammarAction();
int LegendBalancedGrammarAction();
int LegendHeightGrammarAction();

#endif
