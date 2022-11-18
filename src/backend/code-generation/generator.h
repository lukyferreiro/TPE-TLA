#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../support/shared.h"

void Generator(Program* program, FILE* out);
void GeneratorConstantArray(ConstantArray* constantArray, FILE* out);
void GeneratorConstant(Constant* constant, FILE* out);
void GeneratorDeclaration(Declaration* declaration, FILE* out);
void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, FILE* out);
void GeneratorIntegerParameters(IntegerParameters* integerParameters, FILE* out);
void GeneratorIntegerArray(IntegerArray* integerArray, FILE* out);
void GeneratorBlock(Block* block, FILE* out);
void GeneratorLegendParameters(LegendParameters* legendParameters, FILE* out);
void GeneratorConfigureBlock(ConfigureBlock* configureBlock, FILE* out);
void GeneratorTreeSentences(TreeSentences* treeSentences, FILE* out);
void GeneratorTreeSentence(TreeSentence* treeSentence, FILE* out);
void GeneratorCreateBlock(CreateBlock* createBlock, FILE* out);
void GeneratorFileSentences(FileSentences* fileSentences, FILE* out);
void GeneratorFileSentence(FileSentence* fileSentence, FILE* out);
void GeneratorTreeParameters(TreeParameters* treeParameters, FILE* out);
void GeneratorTreeArray(TreeArray* TreeArray, FILE* out);
void GeneratorFileParameter(FileParameter* fileParameter, FILE* out);
void GeneratorLegendParameters(LegendParameters* legendParameters, FILE* out);
void GeneratorLegendArray(LegendArray* legendArray, FILE* out);

// Nodos hoja
void GeneratorInteger(int integer, FILE* out);
void GeneratorTreeType(TreeTypeStruct* type, FILE* out);
void GeneratorLegendType(LegendTypeStruct* type, FILE* out);
void GeneratorTreeName(char* treeName, FILE* out);
void GeneratorFileName(char* fileName, FILE* out);
void GeneratorFilePath(char* FilePath, FILE* out);

#endif
