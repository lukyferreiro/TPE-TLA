#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../support/shared.h"

// Funciones generales
void Generator(Program* program);
void GeneratorConstantArray(ConstantArray* constantArray);
void GeneratorConstant(Constant* constant);
void GeneratorBlock(Block* block);

// Funciones declaration
void GeneratorDeclaration(Declaration* declaration);
void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, int treeIndex);
void GeneratorIntegerParameters(IntegerParameters* integerParameters, int treeIndex, TreeSentenceType sentenceType, TreeType treeType);
void GeneratorIntegerArray(IntegerArray* integerArray, int treeIndex, TreeSentenceType sentenceType, TreeType treeType);

// Funciones configure
void GeneratorConfigureBlock(ConfigureBlock* configureBlock, int treeIndex, TreeType treeType);
void GeneratorTreeSentences(TreeSentences* treeSentences, int treeIndex, TreeType treeType);
void GeneratorTreeSentence(TreeSentence* treeSentence, int treeIndex, TreeType treeType);

// Funciones create
void GeneratorLegendParameters(LegendParameters* legendParameters);
void GeneratorCreateBlock(CreateBlock* createBlock);
void GeneratorFileSentences(FileSentences* fileSentences);
void GeneratorFileSentence(FileSentence* fileSentence);
void GeneratorTreeParameters(TreeParameters* treeParameters);
void GeneratorTreeArray(TreeArray* TreeArray);
void GeneratorFileParameter(FileParameter* fileParameter);
void GeneratorLegendParameters(LegendParameters* legendParameters);
void GeneratorLegendArray(LegendArray* legendArray);

// Nodos hoja
void GeneratorInteger(int value, int treeIndex, TreeSentenceType sentenceType, TreeType treeType);
TreeType GeneratorTreeType(TreeTypeStruct* type, int treeIndex);
void GeneratorLegendType(LegendTypeStruct* type);
int GeneratorTreeName(char* treeName);
void GeneratorFileName(char* fileName);
void GeneratorFilePath(char* FilePath);

// Función para liberar recursos de generatorState
void freeGeneratorState();

#endif
