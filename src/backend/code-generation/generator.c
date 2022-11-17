#include "generator.h"
#include "../semantic-analysis/symbol-table.h"
#include "../support/logger.h"

void Generator(Program* program, FILE* out) {
    GeneratorConstantArray(program->constantArray, out);
}

void GeneratorConstantArray(ConstantArray* constantArray, FILE* out) {
    switch (constantArray->type) {
        case ONE_CONSTANT:
            GeneratorConstant(constantArray->constant, out);
            break;
        case VARIOUS_CONSTANTS:
            GeneratorConstant(constantArray->constant, out);
            GeneratorConstantArray(constantArray->nextConstantArray, out);
            break;
        default:
            break;
    }
}

void GeneratorConstant(Constant* constant, FILE* out) {
    switch (constant->type) {
        case DECLARATION:
            GeneratorDeclaration(constant->declaration, out);
        case BLOCK:
            GeneratorBlock(constant->block, out);
        default:
            break;
    }
}

void GeneratorDeclaration(Declaration* declaration, FILE* out) {
    fprintf(out, "label = \"%s\";\n", declaration->treeName);
    GeneratorDeclartionParameters(declaration->declarationParameters, out);
}

void GeneratorDeclartionParameters(DeclarationParameters* declarationParameters, FILE* out) {
    GeneratorIntegerParameters(declarationParameters->integerParameters, out);
}

void GeneratorIntegerParameters(IntegerParameters* integerParameters, FILE* out) {
    GeneratorIntegerArray(integerParameters->integerArray, out);
}

void GeneratorIntegerArray(IntegerArray* integerArray, FILE* out) {
    switch (integerArray->type) {
        case ONE_INTEGER:
            GeneratorInteger(integerArray->integer->value, out);
            break;
        case VARIOUS_INTEGER:
            GeneratorInteger(integerArray->integer, out);
            GeneratorIntegerArray(integerArray->nextIntegerArray, out);
            break;
        default:
            break;
    }
}

void GeneratorInteger(Integer* integer, FILE* out) {
    fprint(out, "%d;", integer->value);
}

void GeneratorBlock(Block* block, FILE* out) {
    switch (block->type) {
        case CONFIGURE_BLOCK:
            // TODO
            break;
        case CREATE_BLOCK:
            // TODO
            break;
        default:
            break;
    }
}