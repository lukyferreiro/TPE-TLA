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

Program* ProgramGrammarAction(const ConstantArray* constantArray);

ConstantArray* ConstantGrammarAction(const Constant* constant);
ConstantArray* ConstantArrayGrammarAction(const Constant* constant, const ConstantArray* nextConstantArray);

Constant* DeclarationGrammarAction(const Declaration* declaration);
Constant* BlockGrammarAction(const Block* block);

Declaration* DeclarationTreeGrammarAction(const TreeName* treeName, const DeclarationParameters* declarationParameters);

DeclarationParameters* DeclarationTreeParametersGrammarAction(const IntegerParameters* treeIntegersParameters);

IntegerParameters* IntegerParametersGrammarAction(const IntegerArray* nodesIntegerArray);

IntegerArray* IntegerConstantGrammarAction(const Integer* node);
IntegerArray* IntegerConstantArrayGrammarAction(const Integer* node, const IntegerArray* nextNodesIntegerArray);

Block* ConfigureBlockGrammarAction(const TreeType* treeType, const TreeName* treeName, const ConfigureBlock* configureBlock);
Block* CreateBlockGrammarAction(const FileName* fileName, const CreateBlock* createBlock);

TreeType* TreeTypeBSTGrammarAction();
TreeType* TreeTypeAVLGrammarAction();
TreeType* TreeTypeRBTGrammarAction();

ConfigureBlock* TreeSentencesGrammarAction(const TreeSentences* treeSentences);

TreeSentences* TreeSentenceGrammarAction(const TreeSentence* treeSentence);
TreeSentences* TreeSentenceArrayGrammarAction(const TreeSentence* treeSentence, const TreeSentences* nextTreeSentences);

TreeSentence* AddNodeGrammarAction(const IntegerParameters* integerParameters);
TreeSentence* DeleteNodeGrammarAction(const IntegerParameters* integerParameters);
TreeSentence* FindNodeGrammarAction(const IntegerParameters* integerParameters);

CreateBlock* FileSentencesGrammarAction(const FileSentences* fileSentences);

FileSentences* FileSentenceGrammarAction(const FileSentence* fileSentence);
FileSentences* FileSentenceArrayGrammarAction(const FileSentence* fileSentence, const FileSentences* nextFileSentences);

FileSentence* AddTreeGrammarAction(const TreeParameters* treeParameters);
FileSentence* AddFilePathGrammarAction(const TreeParameters* fileParameter);
FileSentence* AddLegendGrammarAction(const TreeParameters* legendParameters);

TreeParameters* TreeParametersGrammarAction(const TreeArray* treeArray);

FileParameter *FileParameterSentenceGrammarAction(const FilePath* filePath);

TreeArray* TreeNameGrammarAction(const TreeName* treeName);
TreeArray* TreeNameArrayGrammarAction(const TreeName* treeName, const TreeArray* nextTreeNames);

LegendParameters* LegendParametersGrammarAction(const LegendArray* legendArray);

LegendArray* LegendTypeGrammarAction(const LegendType* legendType);
LegendArray* LegendTypeArrayGrammarAction(const LegendType* legendType, const LegendArray* nextLegendTypes);

LegendType* LegendMaxGrammarAction();
LegendType* LegendMinGrammarAction();
LegendType* LegendCountGrammarAction();
LegendType* LegendBalancedGrammarAction();
LegendType* LegendHeightGrammarAction();

#endif
