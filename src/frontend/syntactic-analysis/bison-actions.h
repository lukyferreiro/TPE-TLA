#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/semantic-analysis/symbol-table.h"
#include "../../backend/support/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de uir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

Program* ProgramGrammarAction(ConstantArray* ntArray);

ConstantArray* ntGrammarAction(Constant* nt);
ConstantArray* ntArrayGrammarAction(Constant* nt, ConstantArray* nextntArray);

Constant* DeclarationGrammarAction(Declaration* declaration);
Constant* BlockGrammarAction(Block* block);

Declaration* DeclarationTreeGrammarAction(char* treeName, DeclarationParameters* declarationParameters);

DeclarationParameters* DeclarationTreeParametersGrammarAction(IntegerParameters* treeIntegersParameters);

IntegerParameters* IntegerParametersGrammarAction(IntegerArray* nodesIntegerArray);

IntegerArray* IntegerntGrammarAction(int node);
IntegerArray* IntegerntArrayGrammarAction(int node, IntegerArray* nextNodesIntegerArray);

Block* ConfigureBlockGrammarAction(TreeTypeStruct* treeType, char* treeName, ConfigureBlock* configureBlock);
Block* CreateBlockGrammarAction(char* fileName, CreateBlock* createBlock);

TreeTypeStruct* TreeTypeBSTGrammarAction();
TreeTypeStruct* TreeTypeAVLGrammarAction();
TreeTypeStruct* TreeTypeRBTGrammarAction();

ConfigureBlock* TreeSentencesGrammarAction(TreeSentences* treeSentences);

TreeSentences* TreeSentenceGrammarAction(TreeSentence* treeSentence);
TreeSentences* TreeSentenceArrayGrammarAction(TreeSentence* treeSentence, TreeSentences* nextTreeSentences);

TreeSentence* AddNodeGrammarAction(IntegerParameters* integerParameters);
TreeSentence* DeleteNodeGrammarAction(IntegerParameters* integerParameters);
TreeSentence* FindNodeGrammarAction(IntegerParameters* integerParameters);

CreateBlock* FileSentencesGrammarAction(FileSentences* fileSentences);

FileSentences* FileSentenceGrammarAction(FileSentence* fileSentence);
FileSentences* FileSentenceArrayGrammarAction(FileSentence* fileSentence, FileSentences* nextFileSentences);

FileSentence* AddTreeGrammarAction(TreeParameters* treeParameters);
FileSentence* AddFilePathGrammarAction(TreeParameters* fileParameter);
FileSentence* AddLegendGrammarAction(TreeParameters* legendParameters);

TreeParameters* TreeParametersGrammarAction(TreeArray* treeArray);

FileParameter* FileParameterSentenceGrammarAction(char* filePath);

TreeArray* TreeNameGrammarAction(char* treeName);
TreeArray* TreeNameArrayGrammarAction(char* treeName, TreeArray* nextTreeNames);

LegendParameters* LegendParametersGrammarAction(LegendArray* legendArray);

LegendArray* LegendTypeGrammarAction(LegendTypeStruct* legendType);
LegendArray* LegendTypeArrayGrammarAction(LegendTypeStruct* legendType, LegendArray* nextLegendTypes);

LegendTypeStruct* LegendMaxGrammarAction();
LegendTypeStruct* LegendMinGrammarAction();
LegendTypeStruct* LegendCountGrammarAction();
LegendTypeStruct* LegendBalancedGrammarAction();
LegendTypeStruct* LegendHeightGrammarAction();

#endif
