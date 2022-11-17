#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "../../frontend/syntactic-analysis/bison-parser.h"
#include "../support/shared.h"

void Generator(Program* program, FILE* out);
void GeneratorConstantArray(ConstantArray* constantArray, FILE* out);
void GeneratorConstant(Constant* constant, FILE* out);
void GeneratorDeclaration(Declaration* declaration, FILE* out);
void GeneratorDeclartionParameters(DeclarationParameters* declarationParameters, FILE* out);
void GeneratorIntegerParameters(IntegerParameters* integerParameters, FILE* out);
void GeneratorIntegerArray(IntegerArray* integerArray, FILE* out);
void GeneratorInteger(Integer* integer, FILE* out);
void GeneratorBlock(Block* block, FILE* out);

#endif
