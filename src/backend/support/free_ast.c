#include "free_ast.h"
#include "logger.h"


void freeProgram(Program * program) {
    if(program == NULL)
        return;
    freeConstantArray(program->constantArray);
    free(program);
}

void freeConstantArray(ConstantArray* c) {
    if(c == NULL)
        return;
    freeConstant(c->constant);
    freeConstantArray(c->nextConstantArray);
    free(c);
}

void freeConstant(Constant* c) {
    if(c == NULL)
        return;
    freeBlock(c->block);
    freeDeclaration(c->declaration);
    free(c);
}

void freeDeclaration(Declaration* d) {
    if(d == NULL)
        return;
    freeTreeName(d->treeName);
    freeDeclarationParameters(d->declarationParameters);
    free(d);
}   

void freeDeclarationParameters(DeclarationParameters* d){
    if(d == NULL)
        return;
    freeIntegerParameters(d->integerParameters);
    free(d);
}

void freeBlock(Block* b){
    if(b == NULL)
        return;
    freeTreeTypeStruct(b->treeType);
    freeTreeName(b->treeName);
    freeFileName(b->fileName);
    freeConfigureBlock(b->configureBlock);
    freeCreateBlock(b->createBlock);
    free(b);
}

void freeConfigureBlock(ConfigureBlock* c){
    if(c == NULL)
        return;
    freeTreeSentences(c->treeSentences);
    free(c);
}

void freeTreeSentences(TreeSentences* t){
    if(t == NULL)
        return;
    freeTreeSentence(t->treeSentence);
    freeTreeSentences(t->nextTreeSentences);
    free(t);
}

void freeTreeSentence(TreeSentence* t){
    if(t == NULL)
        return;
    freeIntegerParameters(t->integerParameters);
    free(t);
}

void freeCreateBlock(CreateBlock* c){
    if(c == NULL)
        return;
    freeFileSentences(c->fileSentences);
    free(c);
}

void freeFileSentences(FileSentences* f){
    if(f == NULL)
        return;
    freeFileSentence(f->fileSentence);
    freeFileSentences(f->nextFileSentences);
    free(f);
}

void freeFileSentence(FileSentence* f){
    if(f == NULL)
        return;
    freeTreeParameters(f->treeParameters);
    freeFileParameter(f->fileParameter);
    freeLengendParameter(f->legendParameters);
    free(f);
}

void freeTreeParameters(TreeParameters* t){
    if(t == NULL)
        return;
    freeTreeArray(t->treeArray);
    free(t);
}

void freeTreeArray(TreeArray* t){
    if(t == NULL)
        return;
    freeTreeName(t->treeName);
    freeTreeArray(t->nextTreeArray);
    free(t);
}

void freeFileParameter(FileParameter* f){
    if(f == NULL)
        return;
    freeFilePath(f->filePath);
    free(f);
}

void freeLengendParameter(LegendParameters* l){
    if(l == NULL)
        return;
    freeLegendArray(l->legendArray);
    free(l);
}

void freeLegendArray(LegendArray* l){
    if(l == NULL)
        return;
    freeLegendTypeStruct(l->legendType);
    freeLegendArray(l->nextLegendArray);
    free(l);
}

void freeLegendTypeStruct(LegendTypeStruct* l){
    if(l == NULL)
        return;
    free(l);   
}

void freeTreeTypeStruct(TreeTypeStruct* t){
    if(t == NULL)
        return;
    free(t);   
}

void freeIntegerParameters(IntegerParameters* i){
    if(i == NULL)
        return;
    freeIntegerArray(i->integerArray);
    free(i);
}

void freeIntegerArray(IntegerArray* i){
    if(i == NULL)
        return;
    freeIntegerArray(i->nextIntegerArray);
    free(i);
}


void freeTreeName(char* t){
    if(t == NULL)
        return;
    free(t);
}

void freeFileName(char* f){
    if(f == NULL)
        return;
    free(f);
}

void freeFilePath(char* f){
    if(f == NULL)
        return;
    free(f);
}
