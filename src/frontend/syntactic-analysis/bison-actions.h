#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
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

Declaration* DeclarationTreeGrammarAction(TreeName* treeName, DeclarationParameters* declarationParameters);

DeclarationParameters* DeclarationTreeParametersGrammarAction(IntegerParameters* treeIntegersParameters);

IntegerParameters* IntegerParametersGrammarAction(IntegerArray* nodesIntegerArray);

IntegerArray* IntegerntGrammarAction(Integer* node);
IntegerArray* IntegerntArrayGrammarAction(Integer* node, IntegerArray* nextNodesIntegerArray);

Block* ConfigureBlockGrammarAction(TreeType* treeType, TreeName* treeName, ConfigureBlock* configureBlock);
Block* CreateBlockGrammarAction(FileName* fileName, CreateBlock* createBlock);

TreeType* TreeTypeBSTGrammarAction();
TreeType* TreeTypeAVLGrammarAction();
TreeType* TreeTypeRBTGrammarAction();

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

FileParameter* FileParameterSentenceGrammarAction(FilePath* filePath);

TreeArray* TreeNameGrammarAction(TreeName* treeName);
TreeArray* TreeNameArrayGrammarAction(TreeName* treeName, TreeArray* nextTreeNames);

LegendParameters* LegendParametersGrammarAction(LegendArray* legendArray);

LegendArray* LegendTypeGrammarAction(LegendType* legendType);
LegendArray* LegendTypeArrayGrammarAction(LegendType* legendType, LegendArray* nextLegendTypes);

LegendType* LegendMaxGrammarAction();
LegendType* LegendMinGrammarAction();
LegendType* LegendCountGrammarAction();
LegendType* LegendBalancedGrammarAction();
LegendType* LegendHeightGrammarAction();

#endif
