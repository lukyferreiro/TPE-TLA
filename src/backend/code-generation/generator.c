#include "generator.h"
#include "../../backend/support/logger.h"
#include "../../backend/domain-specific/tree_handlers/tree.h"
#include <string.h>
#include <stdlib.h>

#define MAX_NUM_TREES 20
#define LEGEND_TYPES 5

struct FileWithName {
    char* name;
    char* filePath;

    // arreglo con los árboles que va a imprimir
    char* treeNames[MAX_NUM_TREES]; // arreglo con los nombres
    struct node* currentTrees[MAX_NUM_TREES];

    // arreglo de modificadores para el archivo
    LegendType legendParams[LEGEND_TYPES];
};
struct GeneratorState {
    char* treeNames[MAX_NUM_TREES]; // arreglo con los nombres
    struct node* currentTrees[MAX_NUM_TREES];
    int size;
};

static struct GeneratorState* myGeneratorState;

//aux functions
static int findTreeIndexByName(char* treeName);


void Generator(Program* program) {
    // inicializar struct generator state
    myGeneratorState = (struct GeneratorState*)calloc(1, sizeof(struct GeneratorState));
    LogDebug("Generating program");
    GeneratorConstantArray(program->constantArray);
}

void GeneratorConstantArray(ConstantArray* constantArray) {
    LogDebug("Generating ConstantArray");
    switch (constantArray->type) {
        case ONE_CONSTANT:
            GeneratorConstant(constantArray->constant);
            break;
        case VARIOUS_CONSTANTS:;
            GeneratorConstant(constantArray->constant);
            GeneratorConstantArray(constantArray->nextConstantArray);
            break;
        default:
            break;
    }
}

void GeneratorConstant(Constant* constant) {
    LogDebug("Generating Constant");
    switch (constant->type) {
        case DECLARATION:
            GeneratorDeclaration(constant->declaration);
            break;
        case BLOCK:
            GeneratorBlock(constant->block);
            break;
        default:
            break;
    }
}

void GeneratorDeclaration(Declaration* declaration) {
    LogDebug("Generating Declaration");

    //chequear si todavía puedo agregar arboles o no

    // guardo el nombre del nuevo arbol 
    //TODO: ver si se guarda directo o si se hace el strcppy
    myGeneratorState->treeNames[myGeneratorState->size] = malloc(strlen(declaration->treeName) + 1);
    strcpy(myGeneratorState->treeNames[myGeneratorState->size], declaration->treeName);
    // myGeneratorState->treeNames[myGeneratorState->size] = declaration->treeName;

    //inicializo ese arbol en null
    myGeneratorState->currentTrees[myGeneratorState->size] = NULL;

    //incremento el size luego de que paso el index como param, para que las funciones que sigan sepan donde realizar la operacion
    GeneratorDeclarationParameters(declaration->declarationParameters, myGeneratorState->size++);
}

void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, int treeIndex) {
    LogDebug("Generating DeclarationParameters");
    //Por default las declaration se hacen sobre el tipo BST. La operación será obviamente, addNode
    GeneratorIntegerParameters(declarationParameters->integerParameters, treeIndex, ADD_NODE_SENTENCE, BST_TYPE);
}

void GeneratorIntegerParameters(IntegerParameters* integerParameters, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating IntegerParameters");
    GeneratorIntegerArray(integerParameters->integerArray, treeIndex, sentenceType, treeType);
}

void GeneratorIntegerArray(IntegerArray* integerArray, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating IntegerArray");
    switch (integerArray->type) {
        case ONE_INTEGER:
            GeneratorInteger(integerArray->value, treeIndex, sentenceType, treeType);
            break;
        case VARIOUS_INTEGER:
            GeneratorInteger(integerArray->value, treeIndex, sentenceType, treeType);
            GeneratorIntegerArray(integerArray->nextIntegerArray, treeIndex, sentenceType, treeType);
            break;
        default:
            break;
    }
}

void GeneratorBlock(Block* block) {
    LogDebug("Generating Block");
    switch (block->type) {
        case CONFIGURE_BLOCK:
            //Guardo el treeType y el index asociado al nombre para pasar a las funciones siguientes
            GeneratorConfigureBlock(block->configureBlock, GeneratorTreeName(block->treeName),  GeneratorTreeType(block->treeType));
            break;
        case CREATE_BLOCK:
            // crear un struct que sea para los files, con el filename
            // filepath, arreglo de nombres de arboles, etc... ?
            GeneratorFileName(block->fileName);
            GeneratorCreateBlock(block->createBlock);
            break;
        default:
            break;
    }
}

void GeneratorConfigureBlock(ConfigureBlock* configureBlock, int treeIndex, TreeType treeType) {
    LogDebug("Generating ConfigureBlock");
    //Hago el cambio de type de ser necesario antes de empezar a ejecutar las sentencias
    //Si el tipo fuera el mismo, no se hace más que devolver la misma root
    myGeneratorState->currentTrees[treeIndex] = switchType(myGeneratorState->currentTrees[treeIndex], treeType);
    GeneratorTreeSentences(configureBlock->treeSentences, treeIndex, treeType);
}

void GeneratorTreeSentences(TreeSentences* treeSentences, int treeIndex, TreeType treeType) {
    LogDebug("Generating TreeSentences");
    switch (treeSentences->type) {
        case ONE_TREE_SENTENCE:
            GeneratorTreeSentence(treeSentences->treeSentence, treeIndex, treeType);
            break;
        case VARIOUS_TREE_SENTENCES:
            GeneratorTreeSentence(treeSentences->treeSentence, treeIndex, treeType);
            GeneratorTreeSentences(treeSentences->nextTreeSentences, treeIndex, treeType);
            break;
        default:
            break;
    }
}

void GeneratorTreeSentence(TreeSentence* treeSentence, int treeIndex, TreeType treeType) {
    LogDebug("Generating TreeSentence");
    switch (treeSentence->type) {
        case ADD_NODE_SENTENCE:
            // Voy al arbol que haga falta y le inserto el nodo
            // si ya existía el nodo, debería tirar un warning y no generar outputs
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex, ADD_NODE_SENTENCE, treeType);
            break;
        case DELETE_NODE_SENTENCE:
            // Voy al arbol que haga falta y le borro el nodo
            // si no existía el nodo, debería tirar un warning y no generar outputs
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex,  DELETE_NODE_SENTENCE, treeType);
            break;
        case FIND_NODE_SENTENCE:
            // Voy al arbol que haga falta y le seteo al nodo found=true?
            // Si no existía, no hago nada y sigo
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex, FIND_NODE_SENTENCE, treeType);
            break;
        default:
            break;
    }
}

void GeneratorCreateBlock(CreateBlock* createBlock) {
    LogDebug("Generating CreateBlock");
    GeneratorFileSentences(createBlock->fileSentences);
}

void GeneratorFileSentences(FileSentences* fileSentences) {
    LogDebug("Generating FileSentences");
    switch (fileSentences->type) {
        case ONE_FILE_SENTENCE:
            GeneratorFileSentence(fileSentences->fileSentence);
            break;
        case VARIOUS_FILE_SENTENCES:
            GeneratorFileSentence(fileSentences->fileSentence);
            GeneratorFileSentences(fileSentences->nextFileSentences);
            break;
        default:
            break;
    }
}

void GeneratorFileSentence(FileSentence* fileSentence) {
    LogDebug("Generating FileSentence");
    switch (fileSentence->type) {
        case ADD_TREE_SENTENCE:
            // Voy al arbol y lo agrego al archivo
            GeneratorTreeParameters(fileSentence->treeParameters);
            break;
        case ADD_FILE_PATH_SENTENCE:
            // agrego al struct el filepath
            GeneratorFileParameter(fileSentence->fileParameter);
            break;
        case ADD_LEGEND_SENTENCE:
            // agrego a un arreglo de legend parameters el que me pasen
            // O tengo un arreglo de bool a ver si tengo que usarlo o no
            GeneratorLegendParameters(fileSentence->legendParameters);
            break;
        default:
            break;
    }
}

void GeneratorTreeParameters(TreeParameters* treeParameters) {
    LogDebug("Generating TreeParameters");
    GeneratorTreeArray(treeParameters->treeArray);
}

void GeneratorTreeArray(TreeArray* treeArray) {
    LogDebug("Generating TreeArray");
    switch (treeArray->type) {
        case ONE_TREE:
            // Veo como agregar las structs a
            GeneratorTreeName(treeArray->treeName);
            break;
        case VARIOUS_TREES:
            // TODO mmmmmm
            GeneratorTreeName(treeArray->treeName);
            GeneratorTreeArray(treeArray->nextTreeArray);
            break;
        default:
            break;
    }
}

void GeneratorFileParameter(FileParameter* fileParameter) {
    LogDebug("Generating FileParameter");
    GeneratorFilePath(fileParameter->filePath);
}

void GeneratorLegendParameters(LegendParameters* legendParameters) {
    LogDebug("Generating LegendParameters");
    GeneratorLegendArray(legendParameters->legendArray);
}

void GeneratorLegendArray(LegendArray* legendArray) {
    LogDebug("Generating LegendArray");
    switch (legendArray->type) {
        case ONE_LEGEND:
            GeneratorLegendType(legendArray->legendType);
            break;
        case VARIOUS_LEGENDS:
            GeneratorLegendType(legendArray->legendType);
            GeneratorLegendArray(legendArray->nextLegendArray);
            break;
        default:
            break;
    }
}

void GeneratorInteger(int value, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating Integer leaf");
    switch (sentenceType) {
        case ADD_NODE_SENTENCE:
            //Recibo por parámetro el treeType siempre, porque puede llegar a ser la primer inserción y necesitarlo
            if (myGeneratorState->currentTrees[treeIndex] == NULL) {
                myGeneratorState->currentTrees[treeIndex] = insertFirstNode(myGeneratorState->currentTrees[treeIndex], value, treeType);
            } else {
                myGeneratorState->currentTrees[treeIndex] = insertNode(myGeneratorState->currentTrees[treeIndex], value);
            }
            break;
        case DELETE_NODE_SENTENCE:
            myGeneratorState->currentTrees[treeIndex] = deleteNode(myGeneratorState->currentTrees[treeIndex], value);
            break;
        case FIND_NODE_SENTENCE:
            findNode(myGeneratorState->currentTrees[treeIndex], value);
            break;
        default:
            break;
    }
}

TreeType GeneratorTreeType(TreeTypeStruct* type) {
    LogDebug("Generating TreeType leaf");
    return type->treeType;
}

void GeneratorLegendType(LegendTypeStruct* type) {
    // TODO
    LogDebug("Generating LegendType leaf");
    type->legendType;
}

int GeneratorTreeName(char* treeName) {
    LogDebug("Generating TreeName leaf");
    return findTreeIndexByName(treeName);
}

void GeneratorFileName(char* fileName) {
    // TODO
    LogDebug("Generating FileName leaf");
}

void GeneratorFilePath(char* FilePath) {
    // TODO
    LogDebug("Generating FilePath leaf");
}

static int findTreeIndexByName(char* treeName){
    for(int i=0; i<myGeneratorState->size; i++){
        if(strcmp(treeName, myGeneratorState->treeNames[i])==0){
            return i;
        }
    }
    //TODO ver como handlear error
    return -1;
}

void freeGeneratorState(){
    for(int i=0; i<myGeneratorState->size;i++){
        freeTree(myGeneratorState->currentTrees[i]);
        free(myGeneratorState->treeNames[i]);
    }
}