#include "generator.h"
#include "../../backend/support/logger.h"

void Generator(Program* program, FILE* out) {
    GeneratorConstantArray(program->constantArray, out);
}

void GeneratorConstantArray(ConstantArray* constantArray, FILE* out) {
    LogInfo("-----2-----");
    switch (constantArray->type) {
        case ONE_CONSTANT:
            LogInfo("-----2-----");
            GeneratorConstant(constantArray->constant, out);
            break;
        case VARIOUS_CONSTANTS:
        LogInfo("-----2--132121312312---");
            GeneratorConstant(constantArray->constant, out);
            GeneratorConstantArray(constantArray->nextConstantArray, out);
            break;
        default:
        LogInfo("-----132131-----");
            break;
    }
}

void GeneratorConstant(Constant* constant, FILE* out) {
    switch (constant->type) {
        case DECLARATION:
            LogInfo("-----3-----");
            GeneratorDeclaration(constant->declaration, out);
        case BLOCK:
            GeneratorBlock(constant->block, out);
        default:
            break;
    }
}

void GeneratorDeclaration(Declaration* declaration, FILE* out) {
    LogInfo("-----5-----");
    fprintf(out, "label = \"%s\";\n", declaration->treeName);
    GeneratorDeclarationParameters(declaration->declarationParameters, out);
}

void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, FILE* out) {
    GeneratorIntegerParameters(declarationParameters->integerParameters, out);
}

void GeneratorIntegerParameters(IntegerParameters* integerParameters, FILE* out) {
    GeneratorIntegerArray(integerParameters->integerArray, out);
}

void GeneratorIntegerArray(IntegerArray* integerArray, FILE* out) {
    switch (integerArray->type) {
        case ONE_INTEGER:
            GeneratorInteger(integerArray->integer, out);
            break;
        case VARIOUS_INTEGER:
            GeneratorInteger(integerArray->integer, out);
            GeneratorIntegerArray(integerArray->nextIntegerArray, out);
            break;
        default:
            break;
    }
}

void GeneratorBlock(Block* block, FILE* out) {
    switch (block->type) {
        case CONFIGURE_BLOCK:
            GeneratorTreeType(block->treeType, out);
            // TODO mmmmmm
            GeneratorTreeName(block->treeName, out);
            GeneratorConfigureBlock(block->configureBlock, out);
            break;
        case CREATE_BLOCK:
            GeneratorFileName(block->fileName, out);
            GeneratorCreateBlock(block->createBlock, out);
            break;
        default:
            break;
    }
}

void GeneratorConfigureBlock(ConfigureBlock* configureBlock, FILE* out) {
    GeneratorTreeSentences(configureBlock->treeSentences, out);
}

void GeneratorTreeSentences(TreeSentences* treeSentences, FILE* out) {
    switch (treeSentences->type) {
        case ONE_TREE_SENTENCE:
            GeneratorTreeSentence(treeSentences->treeSentence, out);
            break;
        case VARIOUS_TREE_SENTENCES:
            GeneratorTreeSentence(treeSentences->treeSentence, out);
            GeneratorTreeSentences(treeSentences->nextTreeSentences, out);
            break;
        default:
            break;
    }
}

void GeneratorTreeSentence(TreeSentence* treeSentence, FILE* out) {
    switch (treeSentence->type) {
        case ADD_NODE_SENTENCE:
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        case DELETE_NODE_SENTENCE:
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        case FIND_NODE_SENTENCE:
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        default:
            break;
    }
}

void GeneratorCreateBlock(CreateBlock* createBlock, FILE* out) {
    GeneratorFileSentences(createBlock->fileSentences, out);
}

void GeneratorFileSentences(FileSentences* fileSentences, FILE* out) {
    switch (fileSentences->type) {
        case ONE_FILE_SENTENCE:
            GeneratorFileSentence(fileSentences->fileSentence, out);
            break;
        case VARIOUS_FILE_SENTENCES:
            GeneratorFileSentence(fileSentences->fileSentence, out);
            GeneratorFileSentences(fileSentences->nextFileSentences, out);
            break;
        default:
            break;
    }
}

void GeneratorFileSentence(FileSentence* fileSentence, FILE* out) {
    switch (fileSentence->type) {
        case ADD_TREE_SENTENCE:
            GeneratorTreeParameters(fileSentence->treeParameters, out);
            break;
        case ADD_FILE_PATH_SENTENCE:
            GeneratorFileParameter(fileSentence->fileParameter, out);
            break;
        case ADD_LEGEND_SENTENCE:
            GeneratorLegendParameters(fileSentence->legendParameters, out);
            break;
        default:
            break;
    }
}

void GeneratorTreeParameters(TreeParameters* treeParameters, FILE* out) {
    GeneratorTreeArray(treeParameters->treeArray, out);
}

void GeneratorTreeArray(TreeArray* treeArray, FILE* out) {
    switch (treeArray->type) {
        case ONE_TREE:
            // TODO mmmmmm
            GeneratorTreeName(treeArray->treeName, out);
            break;
        case VARIOUS_TREES:
            // TODO mmmmmm
            GeneratorTreeName(treeArray->treeName, out);
            GeneratorTreeArray(treeArray->nextTreeArray, out);
            break;
        default:
            break;
    }
}

void GeneratorFileParameter(FileParameter* fileParameter, FILE* out) {
    GeneratorFilePath(fileParameter->filePath, out);
}

void GeneratorLegendParameters(LegendParameters* legendParameters, FILE* out) {
    GeneratorLegendArray(legendParameters->legendArray, out);
}

void GeneratorLegendArray(LegendArray* legendArray, FILE* out) {
    switch (legendArray->type) {
        case ONE_LEGEND:
            GeneratorLegendType(legendArray->legendType, out);
            break;
        case VARIOUS_LEGENDS:
            GeneratorLegendType(legendArray->legendType, out);
            GeneratorLegendArray(legendArray->nextLegendArray, out);
            break;
        default:
            break;
    }
}

void GeneratorInteger(Integer* integer, FILE* out) {
    fprintf(out, "%d;", integer->value);
}

void GeneratorTreeType(TreeTypeStruct* type, FILE* out) {
    // TODO
    type->treeType;
}

void GeneratorLegendType(LegendTypeStruct* type, FILE* out) {
    // TODO
    type->legendType;
}

void GeneratorTreeName(TreeName* treeName, FILE* out) {
    // TODO
}

void GeneratorFileName(FileName* fileName, FILE* out) {
    // TODO
}

void GeneratorFilePath(FilePath* FilePath, FILE* out) {
    // TODO
}