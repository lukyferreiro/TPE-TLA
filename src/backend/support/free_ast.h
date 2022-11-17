#ifndef __FREE_AST_H_
#define __FREE_AST_H_

#include "shared.h"
#include <string.h>
#include <stdlib.h>

void freeProgram(Program * program);
void freeConstantArray(ConstantArray* c);
void freeConstant(Constant* c);
void freeDeclaration(Declaration* d);
void freeDeclarationParameters(DeclarationParameters* d);
void freeBlock(Block* b);
void freeConfigureBlock(ConfigureBlock* c);
void freeTreeSentences(TreeSentences* t);
void freeTreeSentence(TreeSentence* t);
void freeCreateBlock(CreateBlock* c);
void freeFileSentences(FileSentences* f);
void freeFileSentence(FileSentence* f);
void freeTreeParameters(TreeParameters* t);
void freeTreeArray(TreeArray* t);
void freeFileParameter(FileParameter* f);
void freeLengendParameter(LegendParameters* l);
void freeLegendArray(LegendArray* l);
void freeLegendTypeStruct(LegendTypeStruct* l);
void freeTreeTypeStruct(TreeTypeStruct* t);
void freeIntegerParameters(IntegerParameters* i);
void freeIntegerArray(IntegerArray* i);
void freeInteger(Integer* i);
void freeTreeName(TreeName* t);
void freeFileName(FileName* f);
void freeFilePath(FilePath* f);

#endif